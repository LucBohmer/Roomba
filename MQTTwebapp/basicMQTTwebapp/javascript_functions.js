
function random_Value(){
	var x = Math.floor(Math.random() * 1000);
	return x;
}
	
function move() {
	var elem = document.getElementById("myBar");  
	// x = random_Value();
	var x = document.getElementById("my_text").value;
	elem.style.width = x + '%';
	//document.getElementById("random_Value_").innerHTML = x;
	return x;
}

function time_interval() {
    setInterval(function(){  }, 3000);
}

function load_graph(){
		var chart = new CanvasJS.Chart("chartContainer", { 
		title: {
			text: "Bacterial growth"
		},
		data: [
		{
			type: "line",
			dataPoints: []
		}
		]
	});
	chart.render();	
		
	setInterval(function(){ 
	chart.options.data[0].dataPoints.push({ y: random_Value()});
	chart.render();
	}, 1000);

	$("#addDataPoint").click(function() {
	chart.options.data[0].dataPoints.push({ y: move()});
	chart.render();
	});
}