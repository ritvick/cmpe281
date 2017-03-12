var MongoClient = require('mongodb').MongoClient;

 // Connect to the db
 /**
MongoClient.connect("mongodb://localhost:27017/sensorcloud", function(err, db) {
	console.log('Mongo DB connected');
  if(err) { return console.dir(err); }
MongoDb = db;
  

 

});
**/
MongoClient.connect("mongodb://localhost:27017/sensorcloud").then(function(db) {

	console.log('Mongo DB connected');
	var sensorMetaDataCollection  = db.collection("sensorMetaData");
	var virtualSensorsCollection = db.collection("virtualSensors");
	var coastalSensorDataCollection = db.collection("virtualCoastalSensorData");
	var physicalSensorsDataCollection = db.collection("physicalSensorsData");

	exports.storePhysicalSensorData = function(sensorData) {

		
			physicalSensorsDataCollection.insert(sensorData, {w:1}, function(err, result) {
				console.log(result);
				return "OK";
			});
			
	  	

	}

	exports.getSensorBySensor = function(sensor) {

		return sensorMetaDataCollection.find({"sensor": sensor}).limit(1).toArray().then(function(listOfSensors) {
			if(listOfSensors.length === 0 ) return Promise.reject("Could not sensor with sensor key value" + sensor);
			return listOfSensors[0];
		})

	};

	exports.getAllSensors = function() {
		return sensorMetaDataCollection.find({}).toArray().then(function(listOfSensors) {
			if(listOfSensors.length === 0 ) return Promise.reject("Could not sensor with sensor key value" + sensor);
			
			console.log('Returning List of sensors');

			return listOfSensors;
		});
	};
	exports.getAllVirtualSensors = function() {

		return virtualSensorsCollection.find({status: true}).toArray().then(function(listOfSensors) {
			console.log('sad');
			console.log(JSON.stringify(listOfSensors));
			if(listOfSensors.length === 0 ) return Promise.reject("Could not sensor with sensor key value" + sensor);
			
			console.log('Returning List of sensors');

			return listOfSensors;
		});
	};

	exports.insertSensorData = function(data) {

		return coastalSensorDataCollection.insert(data).then(function(newDoc){

			return newDoc;

		});
	}

});