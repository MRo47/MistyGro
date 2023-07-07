import 'dart:math';
// import 'package:collection/collection.dart';

class PricePoint {
  final double x;
  final double y;

  PricePoint({required this.x, required this.y});
}

List<PricePoint> get pricePoints {
  final Random random = Random();
  final randomNumbers = <double>[];
  final list = <PricePoint>[];
  for (var i = 0; i <= 11; i++) {
    randomNumbers.add(random.nextDouble());
    list.add(PricePoint(x: i.toDouble(), y: random.nextDouble()));
  }

  return list;
}
