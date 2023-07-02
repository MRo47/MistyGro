import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'relay_card.dart';
import 'sensor_card.dart';
import 'manual_input_card.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:intl/intl.dart';
import 'dart:async';

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

enum MenuItem { one, two, three }

class _HomePageState extends State<HomePage> {
  final user = FirebaseAuth.instance.currentUser!;

  DateTime _dateTime = DateTime(0);

  _getDateTime() {
    setState(() {
      _dateTime = DateTime.now();
    });
  }
  // doc ids
  // Future getDocId() async {
  //   // FirebaseDatabase database = FirebaseDatabase.instance;

  // }

  @override
  void initState() {
    _getDateTime();
    // TODO:  DatabaseReference ref = FirebaseDatabase.instance.ref("users/${user.uid}/${DateFormat('yyyy-MM-dd').format(_dateTime)}");
    DatabaseReference ref =
        FirebaseDatabase.instance.ref("users/${user.uid}/2023-06-25");
    // ref.update({"test": 19});
    ref.onValue.listen((event) {
      final data = event.snapshot.value;
      print(data);
    });
    super.initState();
    // Timer.periodic(Duration(seconds: 1), (_) => _getDateTime());
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
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
        body: ListView(
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(
                'Relays',
                style: TextStyle(color: Colors.grey.shade500),
              ),
            ),
            RelayCard(
              name: 'Mister',
              lastUpdate: DateTime.now(),
              icon: Icons.water_drop,
              switchOn: true,
              onColor: Colors.blue,
            ),
            RelayCard(
              name: 'Light',
              lastUpdate: DateTime.now(),
              icon: Icons.light_mode,
              switchOn: true,
              onColor: Colors.amber,
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(
                'Sensors',
                style: TextStyle(color: Colors.grey.shade500),
              ),
            ),
            SensorCard(
              name: 'Temperature',
              lastUpdate: DateTime.now(),
              icon: Icons.thermostat,
              iconColor: Colors.red,
              value: 18.54,
              units: '°C',
            ),
            SensorCard(
              name: 'LDR',
              lastUpdate: DateTime.now(),
              icon: Icons.blur_circular, // Icons.table_chart_rounded,
              iconColor: Colors.deepOrange.shade900,
              value: 4.86,
              units: 'V',
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(
                'Manual inputs',
                style: TextStyle(color: Colors.grey.shade500),
              ),
            ),
            ManualInputCard(
              name: 'pH',
              lastUpdate: DateTime.now(),
              icon: Icons.science, // Icons.table_chart_rounded,
              iconColor: Colors.green,
              initValue: 6.8,
              units: '',
            ),
            ManualInputCard(
              name: 'TDS',
              lastUpdate: DateTime.now(),
              icon: Icons.opacity, // Icons.table_chart_rounded,
              iconColor: Colors.blueGrey,
              initValue: 6.8,
              units: 'ppm',
            ),
          ],
        ));
  }
}
