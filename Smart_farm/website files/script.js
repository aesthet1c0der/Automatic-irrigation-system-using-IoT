setInterval(() => {

          fetch("https://.com/api/read.php")
    .then((response) => {
      return response.json();
    })
    .then((data) => {
      document.getElementById("temp").innerHTML = data.temp;
      document.getElementById("hum").innerHTML = data.hum;
      document.getElementById("moisture").innerHTML = data.moisture;
      document.getElementById("air").innerHTML = data.air;
      
    })
    .catch((err) => {
      console.error(err);
    });

     
}, 100);
