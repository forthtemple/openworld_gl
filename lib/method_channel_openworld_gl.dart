import 'dart:async';
import 'package:flutter/services.dart';
import 'openworld_gl_platform_interface.dart';

const MethodChannel _channel = MethodChannel('openworld_gl');

/// An implementation of [OpenworldGlPlatform] that uses method channels.
class MethodChannelOpenworldGl extends OpenworldGlPlatform {
  bool get isInitialized => this.textureId != null;

  Future<Map<String, dynamic>> initialize_interface(
      {Map<String, dynamic>? options, bool renderToVideo = false}) async {
    final resp = await _channel.invokeMethod(
      'initialize',
      <String, dynamic>{'options': options, 'renderToVideo': renderToVideo},
    );

    this.textureId = resp["textureId"];

    return Map<String, dynamic>.from(resp);
  }

  Future<List<int>> getEgl_interface(int textureId) async {
    final _args = {"textureId": textureId};
   // print("getEgl_interface in");
    final _result = await _channel.invokeMethod('getEgl', _args);
   // print("getEgl_interface out"+_result.toString());

    return List<int>.from(_result);
  }

  Future updateTexture_interface(int textureId, sourceTexture) async {
   // print("method channel updatetexture");
    final _args = {"textureId": textureId, "sourceTexture": sourceTexture};
   // print("method channel updatetextureii"+_args.toString());
    final _result = await _channel.invokeMethod('updateTexture', _args);
    //print("method channel updatetextureiii"+_result.toString());
    return _result;
  }

  Future updateSize_interface(int textureId, Map<String, dynamic> options) async {
    final _args = {
      "textureId": textureId,
      "width": options["width"],
      "height": options["height"],
    };

    final _result = await _channel.invokeMethod('updateSize', _args);

    return _result;
  }

  void dispose_interface(int textureId) async {
    this.isDisposed = true;

    final _args = {"textureId": textureId};
    await _channel.invokeMethod('dispose', _args);
  }
}
