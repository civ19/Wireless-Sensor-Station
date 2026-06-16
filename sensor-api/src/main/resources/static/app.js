async function updateData() {
    const response = await fetch('/weather'); //ask esp for latest Sensor  values
    const data = await response.json(); //

    document.getElementById('temp').textContent = data.temperature + "\u00B0C";
    document.getElementById('light').textContent = data.light + "%";
    document.getElementById('distance').textContent = data.distance + "cm";
}

updateData();
setInterval(updateData, 500);