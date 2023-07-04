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
      elevation: 3,
      shape: RoundedRectangleBorder(
        side: const BorderSide(),
        borderRadius: BorderRadius.circular(15.0), //<-- SEE HERE
      ),
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
                          '$name: ${value.toStringAsFixed(2)} $units',
                          style: const TextStyle(
                              fontSize: 18, fontWeight: FontWeight.bold),
                        ),
                      ),
                      Text(
                        "Last update: ${DateFormat('yyyy-MM-dd HH:mm').format(lastUpdate)}",
                        style: TextStyle(
                            fontSize: 15, color: Colors.grey.shade400),
                      )
                    ],
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.all(10.0),
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
