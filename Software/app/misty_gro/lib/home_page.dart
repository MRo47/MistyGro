import 'package:flutter/material.dart';

import 'package:firebase_database/firebase_database.dart';
import 'package:misty_gro/relay_card.dart';
import 'package:misty_gro/sensor_card.dart';
import 'package:misty_gro/manual_input_card.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:intl/intl.dart';
import 'package:misty_gro/data_utils.dart';
import 'package:misty_gro/chart.dart';

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

enum PageID { home, analytics, settings }

class _HomePageState extends State<HomePage> {
  final user = FirebaseAuth.instance.currentUser!;
  DatabaseReference dataRef = FirebaseDatabase.instance.ref();
  var _pageID = PageID.home;

  List<DataPoint> _temperatureData = <DataPoint>[];
  List<DataPoint> _ldrData = <DataPoint>[];
  List<DataPoint> _misterData = <DataPoint>[];
  List<DataPoint> _lightsData = <DataPoint>[];
  List<DataPoint> _phData = <DataPoint>[];
  List<DataPoint> _tdsData = <DataPoint>[];

  DateTime _dateTime = DateTime(0);

  _getDateTime() {
    setState(() {
      _dateTime = DateTime.now().toUtc();
      Duration offset = _dateTime
          .timeZoneOffset; // TODO: use offset to get last day data for non utc
    });
  }

  _getData(DataSnapshot snapshot) {
    setState(() {
      _temperatureData = getPoints<double>(snapshot.child('temperature'));
      _ldrData = getPoints<double>(snapshot.child('ldr_volts'));
      _misterData = getPoints<bool>(snapshot.child('misters'));
      _lightsData = getPoints<bool>(snapshot.child('lights'));
      _phData = getPoints<double>(snapshot.child('ph'));
      _tdsData = getPoints<double>(snapshot.child('tds'));
    });
  }

  _setPH(value) async {
    dataRef.child('ph').push();

    final Map<String, double> updates = {};
    updates['/ph/${DateTime.now().toUtc().millisecondsSinceEpoch ~/ Duration.millisecondsPerSecond}'] =
        value;

    await dataRef.update(updates);
  }

  _setTDS(value) async {
    dataRef.child('tds').push();

    final Map<String, double> updates = {};
    updates['/tds/${DateTime.now().toUtc().millisecondsSinceEpoch ~/ Duration.millisecondsPerSecond}'] =
        value;

    await dataRef.update(updates);
  }

  @override
  void initState() {
    _getDateTime();
    dataRef = FirebaseDatabase.instance
        .ref("users/${user.uid}/${DateFormat('yyyy-MM-dd').format(_dateTime)}");
    dataRef.onValue.listen((event) {
      _getData(event.snapshot);
    });
    super.initState();
    // Timer.periodic(Duration(seconds: 1), (_) => _getDateTime());
  }

  Widget _getBody() {
    if (_pageID == PageID.home) {
      return ListView(
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
            lastUpdate:
                _misterData.isEmpty ? DateTime(0) : _misterData.last.time,
            icon: Icons.water_drop,
            switchOn: _misterData.isEmpty ? false : _misterData.last.val != 0.0,
            onColor: Colors.blue,
          ),
          RelayCard(
            name: 'Grow lights',
            lastUpdate:
                _lightsData.isEmpty ? DateTime(0) : _lightsData.last.time,
            icon: Icons.light,
            switchOn: _lightsData.isEmpty ? false : _lightsData.last.val != 0.0,
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
            lastUpdate: _temperatureData.isEmpty
                ? DateTime(0)
                : _temperatureData.last.time,
            icon: Icons.thermostat,
            iconColor: Colors.red,
            value: _temperatureData.isEmpty || _temperatureData.last.val < 0.0
                ? 0.0
                : _temperatureData.last.val,
            units: '°C',
          ),
          SensorCard(
            name: 'LDR voltage',
            lastUpdate: _ldrData.isEmpty ? DateTime(0) : _ldrData.last.time,
            icon: Icons.blur_circular, // Icons.table_chart_rounded,
            iconColor: Colors.yellow,
            value: _ldrData.isEmpty ? 0.0 : _ldrData.last.val,
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
            lastUpdate: _phData.isEmpty ? DateTime(0) : _phData.last.time,
            icon: Icons.science, // Icons.table_chart_rounded,
            iconColor: Colors.green,
            initValue: _phData.isEmpty ? 0.0 : _phData.last.val,
            units: '',
            onGotValue: (value) {
              _setPH(value);
            },
          ),
          ManualInputCard(
            name: 'TDS',
            lastUpdate: _tdsData.isEmpty ? DateTime(0) : _tdsData.last.time,
            icon: Icons.opacity, // Icons.table_chart_rounded,
            iconColor: Colors.blueGrey,
            initValue: _tdsData.isEmpty ? 0.0 : _tdsData.last.val,
            units: 'ppm',
            onGotValue: (value) {
              _setTDS(value);
            },
          ),
        ],
      );
    } else if (_pageID == PageID.analytics) {
      return ListView(children: [
        Chart(
          title: "Misters",
          points: _misterData,
          minY: 0,
          maxY: 1.2,
          color: Colors.blue,
        ),
        Chart(
          title: "Lights",
          points: _lightsData,
          minY: 0,
          maxY: 1.2,
          color: Colors.purple,
        ),
        Chart(
          title: 'LDR voltage (V)',
          points: _ldrData,
          minY: 0,
          maxY: 5,
          color: Colors.yellow,
        ),
        Chart(
          title: 'Temperature (°C)',
          points: _temperatureData,
          minY: 0,
          maxY: 45,
          color: Colors.red,
        ),
        Chart(
          title: 'PH',
          points: _phData,
          minY: 0,
          maxY: 14,
          color: Colors.green,
        ),
        Chart(
          title: 'TDS (ppm)',
          points: _tdsData,
          minY: 0,
          maxY: 1500,
          color: Colors.blueGrey,
        ),
      ]);
    } else {
      return const Center(
        child: Text("settings"),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color.fromARGB(255, 50, 50, 50),
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
      bottomNavigationBar: BottomNavigationBar(
        items: const [
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: 'Home',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.show_chart),
            label: 'Analytics',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.settings),
            label: 'Settings',
          ),
        ],
        backgroundColor: Colors.black,
        selectedItemColor: Colors.greenAccent.shade700,
        currentIndex: _pageID.index,
        onTap: (value) {
          setState(() {
            _pageID = PageID.values[value];
          });
        },
      ),
      // Sets the content to the
      // center of the application page
      body: Padding(padding: const EdgeInsets.all(4.0), child: _getBody()),
    );
  }
}
