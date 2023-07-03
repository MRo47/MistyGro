import 'package:flutter/material.dart';
import 'package:intl/intl.dart';

class SensorCard extends StatelessWidget {
  final String name;
  final DateTime lastUpdate;
  final IconData icon;
  final Color iconColor;
  final double value;
  final String units;

  const SensorCard(
      {super.key,
      required this.name,
      required this.lastUpdate,
      required this.icon,
      required this.iconColor,
      required this.value,
      required this.units});

  @override
  Widget build(BuildContext context) {
    return Card(
      child: SizedBox(
        width: double.infinity,
        child: Padding(
          padding: const EdgeInsets.all(15.0),
          child: SizedBox(
            width: MediaQuery.of(context).size.width,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                Expanded(
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: <Widget>[
                      Padding(
                        padding: const EdgeInsets.only(bottom: 20),
                        child: Text(
                          '$name: $value $units',
                          style: const TextStyle(
                              fontSize: 20, fontWeight: FontWeight.bold),
                        ),
                      ),
                      Text(
                        "Last update: ${DateFormat('yyyy-MM-dd kk:mm').format(lastUpdate)}",
                        style:
                            const TextStyle(fontSize: 15, color: Colors.grey),
                      )
                    ],
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.all(15.0),
                  child: Icon(
                    icon,
                    color: iconColor,
                    size: 40,
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
