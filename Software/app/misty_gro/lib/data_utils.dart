library data_utils;

import 'package:firebase_database/firebase_database.dart';
import 'data.dart';

class StampedValue {
  final String value;
  final DateTime timeStamp;

  StampedValue(this.value, this.timeStamp);
}

// class Data {
//   final StampedValue<bool> misters;
//   final StampedValue<bool> light;
//   final StampedValue<double> temperature;
//   final StampedValue<double> ldrVolts;
//   final StampedValue<double> ph;
//   final StampedValue<double> tds;

//   StampedValue<T> fetchLatest<T>(List list){

//   }

//   factory Data.fromJson(Map<String, dynamic> parsedJson) {
//     return Data(
//       parsedJson['ldr_volts'].toString();
//     );
//   }
// }

// StampedValue<double> getLatestDouble(DataSnapshot snapshot) {
//   final children = snapshot.children;
//   int latestTime = 0;
//   double latestValue = 0;
//   for (final child in children) {
//     final timeStamp = int.parse(child.key!);
//     if (timeStamp > latestTime) {
//       latestTime = timeStamp;
//       latestValue = double.parse(child.value.toString());
//     }
//   }
//   return StampedValue(
//       latestValue, DateTime.fromMillisecondsSinceEpoch(latestTime * 1000));
// }

StampedValue? getLatestValue(DataSnapshot snapshot) {
  if (!snapshot.exists) {
    return null;
    //  StampedValue("null", DateTime(0));
  }
  final children = snapshot.children;
  int latestTime = 0;
  String latestValue = '';

  // double latestValue = 0;
  for (final child in children) {
    final timeStamp = int.parse(child.key!);
    if (timeStamp > latestTime) {
      latestTime = timeStamp;
      latestValue = child.value.toString();
    }
  }

  return StampedValue(
      latestValue, DateTime.fromMillisecondsSinceEpoch(latestTime * 1000));
}

List<DataPoint> getPoints<T>(DataSnapshot snapshot) {
  if (!snapshot.exists) {
    return <DataPoint>[];
    //  StampedValue("null", DateTime(0));
  }

  if (T != bool && T != double) {
    throw UnimplementedError("Only bool and double value are supported");
  }

  final children = snapshot.children;

  final points = <DataPoint>[];

  for (final child in children) {
    final timeStamp =
        DateTime.fromMillisecondsSinceEpoch(int.parse(child.key!) * 1000);

    if (T == double) {
      points.add(DataPoint(
          x: timeStamp.hour + timeStamp.minute / 60,
          y: double.parse(child.value.toString())));
    } else if (T == bool) {
      points.add(DataPoint(
          x: timeStamp.hour + timeStamp.minute / 60,
          y: bool.parse(child.value.toString()) ? 1.0 : 0.0));
    }
  }

  return points;
}
