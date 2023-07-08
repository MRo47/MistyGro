import 'dart:math';
// import 'package:collection/collection.dart';

class DataPoint {
  final double x;
  final double y;

  DataPoint({required this.x, required this.y});

  @override
  String toString() {
    // TODO: implement toString
    return "$x, $y\n";
  }
}

List<DataPoint> get dataPoints {
  final Random random = Random();
  final randomNumbers = <double>[];
  final list = <DataPoint>[];
  for (var i = 0; i <= 24; i++) {
    randomNumbers.add(random.nextDouble());
    list.add(DataPoint(x: i.toDouble(), y: random.nextDouble()));
  }

  return list;
}
