import 'dart:async';

import 'openworld_gl_platform_interface.dart';
import 'openGL/OpenGL.dart';
export './openGL/OpenGL.dart';
export './native-array/index.dart';

/// OpenworldGlPlugin
///
/// OpenworldGlPlugin = OpenworldGlPlugin();
/// Map<String, dynamic> _options = {
///     "width": width,
///     "height": height,
///     "antialias": true,
///     "alpha": false
/// };
/// await OpenworldGlPlugin.initialize(options: _options);
class OpenworldGlPlugin extends OpenworldGlPlatform {
  late dynamic openGL;

  late List<int> egls;

  dynamic get gl => openGL.gl;

  // for web
  dynamic get element => openGL.element;

  OpenworldGlPlugin();

  Future<Map<String, dynamic>> initialize(
      {Map<String, dynamic>? options}) async {
   // print("main openworldgl initalize");
    Map<String, dynamic> _options = {};

    _options.addAll(options ?? {});

    final resp = await OpenworldGlPlatform.instance.initialize_interface(options: _options);
   // if (resp.containsKey('textureid'))
      textureId = resp["textureId"];
   // else
   //   textureId=  resp;
    // used for web
    _options["divId"] = textureId.toString();
    openGL = OpenGL().init(_options);

    return resp;
  }

  /// set opengl context for ffi thread
  prepareContext() async {
 //  print("prepare context main texture "+this.textureId!.toString());
  //  try {
   // print("preparecontext");
    egls = await OpenworldGlPlatform.instance.getEgl_interface(this.textureId!);
   // print("preparecontextii"+egls.toString());

   // await OpenworldGlPlatform.instance.getEgl_interface(this.textureId!);
    await Future.delayed(const Duration(milliseconds: 1000), () async {
      openGL.makeCurrent(egls);
    });
    //print("preparecontextiii");
    //} catch (error) {
    //  ... // executed for errors of all types other than Exception
    // print('errr!');
    //}
  }

  /// get created opengl context from native
  Future<List<int>> getEgl(int textureId) async {
    var result =
        List<int>.from(await OpenworldGlPlatform.instance.getEgl_interface(textureId));
    return result;
  }

  /// update texture to flutter
  Future updateTexture(sourceTexture) async {
    //print("updatetext in openworld_gl"+this.textureId.toString()+ " "+sourceTexture.toString());
    return await OpenworldGlPlatform.instance.updateTexture_interface(this.textureId!, sourceTexture);
  }

  dispose() {
  //  print("main dispose");
    return OpenworldGlPlatform.instance.dispose_interface(this.textureId!);
  }
}
