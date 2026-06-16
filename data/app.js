async function updateData() {
    const response = await fetch('/data'); //ask esp for latest Sensor  values
    const data = await response.json(); //

    document.getElementById('temp').textContent = data.temperature + "C";
    document.getElementById('light').textContent = data.light + "%";
    document.getElementById('distance').textContent = data.distance + "cm";
}

updateData();
setInterval(updateData, 500);