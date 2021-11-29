import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Initiate list of transactions of the user
    transactions = []

    # Set the intial sum as 0
    total_sum = 0

    # Retrieve the user's data
    rows = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    
    # Add each of the user's purchase to the list of transcation; search for the price of the stock using the lookup function
    for row in rows:
        transactions.append({"symbol": row["symbol"], "name": lookup(row["symbol"])["name"], "shares": row["shares"], "price": lookup(row["symbol"])["price"], "total": row["shares"] * lookup(row["symbol"])["price"]})
        # Calculate the cost by multiplying the number of shares and price and updating the total sum
        total_sum += row["shares"] * lookup(row["symbol"])["price"]

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    return render_template("index.html", transactions=transactions, cash=cash, total_sum=total_sum + cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Check if symbol is submitted
        if not request.form.get("symbol"):
            return apology("Must provide symbol")

        # Check if valid symbol is submitted
        if not lookup(request.form.get("symbol")):
            return apology("Must provide valid symbol")

        # Check if integer shares is provided
        if not (request.form.get("shares").isdigit() and int(request.form.get("shares")) > 0):
            return apology("Must provide positive integer number of shares")

        # Lookup in dictionary the symbol, price, and time, then store
        d = lookup(request.form.get("symbol"))
        symbol = d["symbol"]
        price = d["price"]
        time = datetime.datetime.now()

        # Store the number of shares and the total price
        shares = int(request.form.get("shares"))
        total = price * shares

        # Insert cash
        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = rows[0]["cash"]

        # If the user does not have enough cash, apologize
        if total > cash:
            return apology("Not enough cash")

        # Insert new data into transactions table
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, shares, price, time)

        # Select everything where symbol is a match for user's input and insert session at user id, symbol, and shares
        if len(db.execute("SELECT * FROM stocks WHERE symbol = ?", symbol)) == 0:
            db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES (?, ?, ?)", session["user_id"], symbol, shares)
        else:
            user_shares = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["shares"]
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?", user_shares + shares, session["user_id"], symbol)

        # Update cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Add and retrieve person information to the list
    rows = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        
        # Ensure that the user provides a symbol
        if not request.form.get("symbol"):
            return apology("Must provide symbol")

        # Ensure that the user enters a valid a symbol
        if not lookup(request.form.get("symbol")):
            return apology("Must provide valid symbol")

        # Lookup information about the stock
        d = lookup(request.form.get("symbol"))
        name = d["name"]
        symbol = d["symbol"]
        price = d["price"]

        return render_template("quoted.html", name=name, symbol=symbol, price=price)

    else:

        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":

        # Ensure that the user enters a username
        if not request.form.get("username"):
            return apology("Must provide username")

        # Get information about the user's assoicated login information
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensures that the user doesn't have an existing account
        if len(rows) != 0:
            return apology("User already exists")

        # Ensure that a valid password is entered, a confirmation is entered, and that the password matches the confirmation
        if not request.form.get("password") or not request.form.get("confirmation") or request.form.get("password") != request.form.get("confirmation"):
            return apology("Invalid password")

        # Ensure that password has at least 8 characters
        if len(request.form.get("password")) < 8:
            return apology("Password must be at least 8 characters")

        # Ensure that password has upper and lowercase characters
        if request.form.get("password") == request.form.get("password").lower() or request.form.get("password") == request.form.get("password").upper():
            return apology("Password must have a mix of upper and lowercase characters")

        # Ensure that password has ! or @
        if "!" not in request.form.get("password") and "@" not in request.form.get("password"):
            return apology("Password must have symbols (!, @)")

        # Add the new password to the hash table
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",  request.form.get("username"), hash)

        return redirect("/")

    else:

        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        # Ensure that symbol is valid
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("Must provide valid symbol")

        # Ensure that shares is valid
        if not (request.form.get("shares").isdigit() and int(request.form.get("shares")) > 0):
            return apology("Must provide positive integer number of shares")

        # Get user_shares and shares
        user_shares = db.execute("SELECT shares FROM stocks WHERE user_id = ?", session["user_id"])[0]["shares"]
        shares = int(request.form.get("shares"))

        # Ensure that user has enough shares
        if user_shares < shares:
            return apology("Not enough shares")

        # Get lookup
        d = lookup(request.form.get("symbol"))
        symbol = d["symbol"]
        price = d["price"]
        time = datetime.datetime.now()

        # Get total price
        shares *= -1
        total = shares * price

        # Get user cash
        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = rows[0]["cash"]

        # Update transactions table
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, shares, price, time)

        # Update stocks table
        user_shares = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["shares"]
        if user_shares + shares == 0:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        else:
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?", user_shares + shares, session["user_id"], symbol)

        # Update user cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, session["user_id"])

        return redirect("/")

    else:

        # Get information about the user's stocks
        rows = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])

        return render_template("sell.html", rows=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
