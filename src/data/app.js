async function updateData() {
    const response = await fetch('/data'); //ask esp for latest Sensor  values
    const data = await response.json(); //

    document.getElementById('temp').textContent = data.temperature;
    document.getElementById('light').textContent = data.light + "%";
    document.getElementById('distance').textContent = data.distnace + "cm";
}

updateData();
setInterval(updateData, 500);