#include "include/openworld_gl/openworld_gl_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <flutter_linux/fl_view.h>
#include <sys/utsname.h>
#include <glib.h>

#include <GL/glew.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <cstring>
#include <iostream>
#include <memory>
#include <future>
#include <chrono>
#include <map>
#include <fstream>
//#include <utility>
#include <iomanip>
#include <ctime>
//#include <chrono>
#include <thread>

#include <X11/Xlib.h>
#include <mutex>

#include "include/fl_my_texture_gl.h"
//#include "../src/ffi.h"
//#include "../src/common.h"
//#include "include/test.h"
//#include "include/customrender.h"

G_DEFINE_TYPE(OpenworldGlPlugin, openworld_gl_plugin, g_object_get_type())

#define EGL_EGLEXT_PROTOTYPES

static void mylog(const std::string& input)
{


    //cout << input << endl;
}

//CustomRender *render = nullptr;
//std::map<int64_t, std::unique_ptr<CustomRender>> renders_;//unique_ptr<CustomRender>> renders_;

//mutable
std::mutex mutex_;

// Called when a method call is received from Flutter.
static void openworld_gl_plugin_handle_method_call(
	OpenworldGlPlugin *self,
	FlMethodCall *method_call)
{
    /*std::ofstream outfile;
    outfile.open("/home/glennlinde/secondtemple.log", std::ios::out);//, std::ios_base::app);//std::ios_base::app
    outfile << "openworld_gl_plugin_handle_method_call";*/

 //   gdk_threads_init ();
  //  gdk_threads_enter ();

 //   gtk_init(NULL,NULL);

 //   XInitThreads();
    //printf(".... openworld_gl_plugin_handle_method_call\n");
	g_autoptr(FlMethodResponse) response = nullptr;

	const gchar *method = fl_method_call_get_name(method_call);
	// Get Dart arguments
	FlValue *args = fl_method_call_get_args(method_call);

	/********************************************/
	/*** CREATE SURFACE *************************/
	/********************************************/
	if (strcmp(method, "initialize") == 0)  //createSurface
	{
        printf(".... initialize here\n");
      //  XInitThreads();


        FlValue *options =  fl_value_lookup_string(args, "options");
		//int width =  0;//fl_value_lookup_string(options, "width");;
		//int height = 0;//fl_value_lookup_int(options, "height");;
		FlValue *w = fl_value_lookup_string(options, "width");
		FlValue *h = fl_value_lookup_string(options, "height");
     //   FlValue *dpr = fl_value_lookup_string(options, "dpr");
       // printf(".... dpr %f\n",fl_value_get_float(dpr)); 1.000


        if (w != nullptr)
			self->width =  fl_value_get_int(w);
		if (h != nullptr)
            self->height = fl_value_get_int(h);
		if (self->width == 0 || self->height == 0)
		{
			response = FL_METHOD_RESPONSE(fl_method_error_response_new(
				"100",
				"MethodCall createSurface() called without passing width and height parameters!",
				nullptr));
		}
		else
		{

			if (self->context != nullptr &&
				self->myTexture->width == self->width &&
				self->myTexture->height == self->height)
			{
                printf("....  shouldnt be here\n");
				// g_autoptr(FlValue) result = fl_value_new_int(-1);
				// response = FL_METHOD_RESPONSE(fl_method_success_response_new(result));
				fl_texture_registrar_unregister_texture(self->texture_registrar, self->texture);
				//if (getRenderer() != nullptr)
				//	stopThread();
			}

           // printf(".... initialize %ld %ld\n",self->texture_registrar, self->width);
            printf(".... initialize  %d %d\n",self->width,self->height);
            //gtk_init();
            self->window = gtk_widget_get_parent_window(GTK_WIDGET(self->fl_view));


        //    self->context = gdk_window_create_gl_context(self->window, &error);
            CustomRender *customRender = new CustomRender(self->width,self->height,self->texture_registrar, self->window);//context);
            self->render=customRender;
            //self->window);//std::make_unique<CustomRender>(width, height);//, texture_registrar_, m_hWnd);

            int64_t textureID = customRender->texture_id();

            printf(".... textureid %ld\n",textureID);

            g_autoptr(FlValue) data = fl_value_new_map();
            // check out https://gitlab.novinparva.com/medga/flutter/-/blob/3.16.9/examples/texture/linux/my_application.cc
            fl_value_set(data, fl_value_new_string("textureId"), fl_value_new_int(textureID));//fl_value_new_int(reinterpret_cast<int64_t>(self->texture)));

            response = FL_METHOD_RESPONSE(fl_method_success_response_new(data));//result));
		}

	} // end createSurface
    else if (strcmp(method, "getEgl") == 0)  //createSurface
    {
    //    mutex_.lock();
        printf(".... getegl\n");

        g_autoptr(FlValue) fl_vector =self->render->getEgls();
        printf(".... getegl render getegls\n");

      //  gdk_gl_context_clear_current();
        response = FL_METHOD_RESPONSE(fl_method_success_response_new(fl_vector));

    }
    else if (strcmp(method, "updateTexture") == 0)  //createSurface
    {
       // gdk_window_show (self->window);
       // printf(".... update texture %d\n",self->width);//renders_.size());

        int textureId = fl_value_get_int(fl_value_lookup_string(args, "textureId"));
        int sourceTexture  = fl_value_get_int(fl_value_lookup_string(args, "sourceTexture"));
    //    printf(".... update texture vals %ld %ld\n",textureId, sourceTexture);

        int data = self->render->updateTexture( sourceTexture );

        response = FL_METHOD_RESPONSE(fl_method_success_response_new(fl_value_new_int(data)));

    }    else if (strcmp(method, "dispose") == 0)
    {
        printf(".... dispose in self\n");

         g_autoptr(FlValue) result = fl_value_new_null();
        response = FL_METHOD_RESPONSE(fl_method_success_response_new(result));

    }
    else
	{
		response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
	}

    //mylog("call respond");
	fl_method_call_respond(method_call, response, nullptr);
  //  printf(".... call respond out\n");
    //gdk_threads_leave ();

    // mylog("call respond out");
}

static void openworld_gl_plugin_dispose(GObject *object)
{
    printf(".... displose\n");
	G_OBJECT_CLASS(openworld_gl_plugin_parent_class)->dispose(object);
}

static void openworld_gl_plugin_class_init(OpenworldGlPluginClass *klass)
{
    printf(".... class init\n");

    G_OBJECT_CLASS(klass)->dispose = openworld_gl_plugin_dispose;
}

static void openworld_gl_plugin_init(OpenworldGlPlugin *self) {}

static void method_call_cb(FlMethodChannel *channel, FlMethodCall *method_call,
						   gpointer user_data)
{
    //printf(".... method_call_cb\n");
	OpenworldGlPlugin *plugin = OPENWORLD_GL_PLUGIN(user_data);
    //mylog("method call in");
	openworld_gl_plugin_handle_method_call(plugin, method_call);
    //mylog("method call out");
}

void openworld_gl_plugin_register_with_registrar(FlPluginRegistrar *registrar)
{
    printf(".... register with register\n");
   // mylog("with register");
	OpenworldGlPlugin *plugin = OPENWORLD_GL_PLUGIN(
		g_object_new(openworld_gl_plugin_get_type(), nullptr));

	FlView *fl_view = fl_plugin_registrar_get_view(registrar);
	plugin->fl_view = fl_view;
	plugin->texture_registrar =
		fl_plugin_registrar_get_texture_registrar(registrar);
  //  printf(".... registerar %ld\n",plugin->texture_registrar);

	g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
	g_autoptr(FlMethodChannel) channel =
		fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                              "openworld_gl",
							 // "openworld_gl_plugin",
							  FL_METHOD_CODEC(codec));
	fl_method_channel_set_method_call_handler(
		channel,
		method_call_cb,
		g_object_ref(plugin),
		g_object_unref);

	// Initialize GL
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		return;
	}

	g_object_unref(plugin);
}

extern  int makeCurrent(GdkGLContext* context)
{
   // printf(".... make current %ld\n",context);
    //gdk_gl_context_set_use_es(context,TRUE);//self->main_context, TRUE);
//    gdk_gl_context_set_use_es(context,FALSE);//self->resource_context, TRUE);
    //mylog("make current in");
    //gdk_gl_context_clear_current();//self->context);
  //  try {
       /* gdk_gl_context_set_debug_enabled (
                 context,
                true
        );
        mylog("make current done debug");*/
       // GError *error = NULL;
   // XInitThreads();
/*    g_autoptr(GError) error = nullptr;
    gdk_gl_context_realize (
            context,
            &error
    );
    if( error != NULL )
    {
        mylog("make current realize failure");
        std::cout << error->message << std::endl;
        g_clear_error (&error);
    } else
        mylog("make current realize fine");*/
   // __try
   // {
      //  try
       // {
   // GdkGLContext* contextcurrent=gdk_gl_context_get_current();
    //if (contextcurrent!=context) {
   //     mylog("make current ");
   // mutex_.lock();
        gdk_gl_context_make_current(context);
  //  mutex_.unlock();
      //  gdk_gl_context_make_current(context);
  //  } else {
      // mylog("make current same");
      //  printf(".... makecurrent same\n");
 //   }
      //  }
       // catch (std::exception& e)
      //  {
       //     mylog("make current mmm");

         //   printf(".... make currenti %ld\n",context);
            // C++ exception handling
       // }
   // }
  //  __except(HandleStructuredException())
 //   {
        // SEH handling
      //  printf(".... make currentii %ld\n",context);
  //  }

    /*CPPTRACE_TRY {
            gdk_gl_context_make_current(context);//self->context);
    } CPPTRACE_CATCH(const std::exception& e) {
        std::cerr<<"Exception: "<<e.what()<<std::endl;
        cpptrace::from_current_exception().print();
    }*/
    //} catch (...) {
   //     mylog("make current err");

    //}
  //  mylog("make current out");
    return 1;
}
