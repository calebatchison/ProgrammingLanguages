// code.js
document.addEventListener("DOMContentLoaded", function() {
    document.getElementById("dataForm").addEventListener("submit", function(e) {
        e.preventDefault();

        const firstName = document.getElementById("firstName").value.trim();
        const lastName = document.getElementById("lastName").value.trim();
        const address = document.getElementById("address").value.trim();
        const city = document.getElementById("city").value.trim();
        const state = document.getElementById("state").value.trim();
        const zip = document.getElementById("zip").value.trim();
        const weightPounds = parseFloat(document.getElementById("weight").value);
        const heightInches = parseFloat(document.getElementById("height").value);

        const weightOunces = weightPounds * 16;
        const heightFeet = heightInches / 12;

        const data = {
            firstName,
            lastName,
            address,
            city,
            state,
            zip,
            weightPounds,
            weightOunces,
            heightInches,
            heightFeet
        };

        alert(JSON.stringify(data, null, 2));
    });
});