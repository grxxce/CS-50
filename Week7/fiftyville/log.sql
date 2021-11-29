-- Keep a log of any SQL queries you execute as you solve the mystery.
-- We know the crime took place on July 28, 2021 on Humphrey Street
-- Looking at the structure of the tables in SQL
.schema

-- Investigate the crime scene report
SELECT * FROM crime_scene_reports
WHERE year = "2021" AND month = "7" AND street = "Humphrey Street";
/* From this, we know that Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. 
Interviews were conducted today with three witnesses who were present at the time 
each of their interview transcripts mentions the bakery */


-- Now I am interested in interviews, so look at that schema
SELECT * FROM interviews 
WHERE year = "2021" AND month = "7" AND day = "28" AND transcript LIKE "%bakery%";

-- 1. Look at flights to fiftyville on the 29th and find who bought tickets. These were the people on the phone with the theif
SELECT * FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE city = "Fiftyville" AND year = "2021" AND month = "7" AND day = "29"
ORDER BY hour
LIMIT 1;

-- Now we know the airport id is 8 and the destination is 4, so we find the escaped place by
SELECT * FROM airports
WHERE id = 4;
-- ANSWER: The city the thief ESCAPED TO: LaGuardia Airport, New York City

-- Now we find the phone calls were this was the receiver and they called for less than a minute on that day
SELECT * FROM passengers
JOIN flights on flights.id = passengers.flight_id
WHERE flight_id = "36";

SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    JOIN flights on flights.id = passengers.flight_id
    WHERE flight_id = "36"
);

SELECT * FROM phone_calls 
WHERE caller IN (
    SELECT phone_number FROM people
    WHERE people.passport_number IN (
        SELECT passport_number FROM passengers
        WHERE flight_id = "36"
    )
) AND year = "2021" AND month = "7" AND day = "28" AND duration < 60;

-- This is the accomplice
SELECT * FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls 
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE people.passport_number IN (
            SELECT passport_number FROM passengers
            WHERE flight_id = "36"
        )
    ) AND year = "2021" AND month = "7" AND day = "28" AND duration < 60
);

-- 2. Find all cars that left within 10:15 and 10:25pm on the 28th of july 2021
SELECT * FROM bakery_security_logs
WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute > 15 AND minute < 25;

SELECT * FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute > 15 AND minute < 25
);

-- 3. We also know a visit was made to the ATM by the caller
SELECT * FROM atm_transactions 
WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street";

-- Find the name that overlaps between atm withdrawels and cars that left by joining on bank account and person_id with account number and name
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street"
);

-- Find the intersection of the people who drove away and the withdrawels
SELECT * FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute > 15 AND minute < 25
)

INTERSECT

SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street"
)

INTERSECT

SELECT * FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls 
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE people.passport_number IN (
            SELECT passport_number FROM passengers
            WHERE flight_id = "36"
        )
    ) AND year = "2021" AND month = "7" AND day = "28" AND duration < 60
);

-- ANSWER: Therefore Bruce is the caller

SELECT * FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls 
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE people.passport_number IN (
            SELECT passport_number FROM passengers
            WHERE flight_id = "36"
        )
    ) AND year = "2021" AND month = "7" AND day = "28" AND duration < 60 AND caller = "(367) 555-5533"
);

-- ANSWER: Therefore Robin is the accomplice