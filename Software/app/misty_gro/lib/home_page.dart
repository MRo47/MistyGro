import 'package:flutter/material.dart';
import 'relay_card.dart';
import 'sensor_card.dart';
import 'manual_input_card.dart';

class HomePage extends StatelessWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          actions: const <Widget>[
            Padding(
              padding: EdgeInsets.only(right: 15),
              child: Icon(Icons.menu),
            ),
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
