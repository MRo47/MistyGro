import 'dart:math';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'relay_card.dart';
import 'sensor_card.dart';
import 'manual_input_card.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:intl/intl.dart';
import 'dart:async';
import 'dart:convert';
import 'data_utils.dart' as data_utils;

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

enum MenuItem { one, two, three }

class _HomePageState extends State<HomePage> {
  final user = FirebaseAuth.instance.currentUser!;
  var _misterStamped = data_utils.StampedValue("false", DateTime(0));
  var _lightsStamped = data_utils.StampedValue("false", DateTime(0));
  var _temperatureStamped = data_utils.StampedValue("0.0", DateTime(0));
  var _ldrStamped = data_utils.StampedValue("0.0", DateTime(0));
  var _phStamped = data_utils.StampedValue("0.0", DateTime(0));
  var _tdsStamped = data_utils.StampedValue("0.0", DateTime(0));
  // bool _check = false;

  DateTime _dateTime = DateTime(0);

  _getDateTime() {
    setState(() {
      _dateTime = DateTime.now();
    });
  }

  _getData(DataSnapshot snapshot) {
    setState(() {
      _misterStamped = data_utils.getLatestValue(snapshot.child('misters')) ??
          data_utils.StampedValue("false", DateTime(0));
      _lightsStamped = data_utils.getLatestValue(snapshot.child('lights')) ??
          data_utils.StampedValue("false", DateTime(0));
      _temperatureStamped =
          data_utils.getLatestValue(snapshot.child('temperature')) ??
              data_utils.StampedValue("0.0", DateTime(0));
      _ldrStamped = data_utils.getLatestValue(snapshot.child('ldr_volts')) ??
          data_utils.StampedValue("0.0", DateTime(0));
      _phStamped = data_utils.getLatestValue(snapshot.child('ph')) ??
          data_utils.StampedValue("0.0", DateTime(0));
      _tdsStamped = data_utils.getLatestValue(snapshot.child('tds')) ??
          data_utils.StampedValue("0.0", DateTime(0));
    });
  }

  @override
  void initState() {
    _getDateTime();
    // TODO:  DatabaseReference ref = FirebaseDatabase.instance.ref("users/${user.uid}/${DateFormat('yyyy-MM-dd').format(_dateTime)}");
    DatabaseReference ref =
        FirebaseDatabase.instance.ref("users/${user.uid}/2023-06-25");
    // ref.update({"test": 19});
    ref.onValue.listen((event) {
      _getData(event.snapshot);
    });
    super.initState();
    // Timer.periodic(Duration(seconds: 1), (_) => _getDateTime());
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: Colors.grey.shade800,
        appBar: AppBar(
          actions: <Widget>[
            Padding(
                padding: const EdgeInsets.only(right: 15),
                child: IconButton(
                  onPressed: () {
                    FirebaseAuth.instance.signOut();
                  },
                  icon: const Icon(Icons.logout),
                )),
          ],
          // leading:
          title: const Row(
            children: [
              Text('MistyGro'),
              Image(
                image: AssetImage('assets/mistygro_512.png'),
                width: 45,
              ),
            ],
          ),
          titleTextStyle: const TextStyle(
            fontSize: 40,
            fontWeight: FontWeight.bold,
            // color: Colors.teal,
          ),
          toolbarHeight: 70,
          backgroundColor: Colors.black,
        ),
        // Sets the content to the
        // center of the application page
        body: Padding(
          padding: const EdgeInsets.all(4.0),
          child: ListView(
            children: <Widget>[
              Padding(
                padding: const EdgeInsets.all(8.0),
                child: Text(
                  'Relays',
                  style: TextStyle(color: Colors.grey.shade300),
                ),
              ),
              RelayCard(
                name: 'Mister',
                lastUpdate: _misterStamped.timeStamp,
                icon: Icons.water_drop,
                switchOn: bool.parse(_misterStamped.value),
                onColor: Colors.blue,
              ),
              RelayCard(
                name: 'Grow lights',
                lastUpdate: _lightsStamped.timeStamp,
                icon: Icons.light,
                switchOn: bool.parse(_lightsStamped.value),
                onColor: Colors.purple.shade500,
              ),
              Padding(
                padding: const EdgeInsets.all(8.0),
                child: Text(
                  'Sensors',
                  style: TextStyle(color: Colors.grey.shade300),
                ),
              ),
              SensorCard(
                name: 'Temperature',
                lastUpdate: _temperatureStamped.timeStamp,
                icon: Icons.thermostat,
                iconColor: Colors.red,
                value: double.parse(_temperatureStamped.value),
                units: '°C',
              ),
              SensorCard(
                name: 'LDR voltage',
                lastUpdate: _ldrStamped.timeStamp,
                icon: Icons.blur_circular, // Icons.table_chart_rounded,
                iconColor: Colors.yellow,
                value: double.parse(_ldrStamped.value),
                units: 'V',
              ),
              Padding(
                padding: const EdgeInsets.all(8.0),
                child: Text(
                  'Manual inputs',
                  style: TextStyle(color: Colors.grey.shade300),
                ),
              ),
              ManualInputCard(
                name: 'PH',
                lastUpdate: _phStamped.timeStamp,
                icon: Icons.science, // Icons.table_chart_rounded,
                iconColor: Colors.green,
                initValue: double.parse(_phStamped.value),
                units: '',
              ),
              ManualInputCard(
                name: 'TDS',
                lastUpdate: _tdsStamped.timeStamp,
                icon: Icons.opacity, // Icons.table_chart_rounded,
                iconColor: Colors.blueGrey,
                initValue: double.parse(_tdsStamped.value),
                units: 'ppm',
              ),
            ],
          ),
        ));
  }
}
