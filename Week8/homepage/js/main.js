// This code was inspired by the followign github repo: https://github.com/akashyap2013/PortFolio_Website/blob/master/js/main.js

$(document).ready(function(){
    let $buttons = $('.project-area .content-type button');

    $buttons.click(function (e){
        // Remove active class from the previous button
        $('.project-area .content-type button').removeClass('active');
        e.target.classList.add('active');

        let selector = $(e.target).attr('data-filter');
        $('.project-area .grid').isotope({
            filter : selector
        });

        return false;
    })
});