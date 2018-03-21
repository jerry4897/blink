const express = require('express')
const app = express()
const fs = require('fs')

app.get('/', (req, res) => res.send('Hello World!'))

var seq = 0
app.get('/update', function(req,res) {

	fs.appendFile('log.txt', JSON.stringify(req.query)+"\n", function (err) {
		if (err) throw err
		console.log("%j", req.query)
		res.send("Got "+ String(seq++) +" "+ JSON.stringify(req.query))
	});	
})

app.get('/get', function(req,res) {
	var arr = fs.readFileSync('log.txt').toString().split("\n"); 
	var result = "";
	var count = parseInt(Object.values(req.query));
	for(var i = arr.length-count-1 ; i < arr.length ; i++){
		console.log(arr[i]);
		result = result + arr[i];	
		result = result + '<br>';	
	}
	res.send(result);
})

app.listen(3000, () => console.log('Example app listening on port 3000!'))
