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
    std::ofstream myfile;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    myfile.open("/home/skinhat/secondtemple.log",std::ios_base::app);
    //std::cout << myfile.is_open() << std::endl;
    myfile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " " << input<< "\n";
    myfile.close();

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
    printf(".... openworld_gl_plugin_handle_method_call\n");
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

        //    background_color(Gtk.StateFlags.NORMAL,Gdk.RGBA(1.0,0.0,0.0,1);
               /* show all windows */

            //gtk_main();     /* pass control to gtk event-loop */
       //    self->window =  gtk_widget_get_window(GTK_WIDGET(self->fl_view));
         //  win);
           // gtk_widget_register_window(GTK_WIDGET(self->fl_view), self->window);
            // gtk_widget_set_window(GTK_WIDGET(self->fl_view), self->window);
            // gdk_window_show(self->window);
          //  self->window = gtk_widget_get_window(GTK_WIDGET(self->fl_view));//gtk_widget_get_parent_window(GTK_WIDGET(self->fl_view));

            // GtkAllocation allocation;
          //   gtk_widget_get_allocation(widget, &allocation);
          //   GdkWindowAttr window_attributes;
            // window_attributes.window_type = GDK_WINDOW_CHILD;
            // window_attributes.x = 100; //allocation.x;
            // window_attributes.y = 100; //allocation.y;
            // window_attributes.width = 200; //allocation.width;
            // window_attributes.height = 400; //allocation.height;
            // window_attributes.wclass = GDK_INPUT_OUTPUT;
            // window_attributes.event_mask =
            //     gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK |
            //     GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK |
            //     GDK_BUTTON_RELEASE_MASK | GDK_SCROLL_MASK | GDK_SMOOTH_SCROLL_MASK |
            //     GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK;
            // gint window_attributes_mask = GDK_WA_X | GDK_WA_Y;

             //GdkWindow *viewWindow =
             //    gdk_window_new(gtk_widget_get_window(widget), &window_attributes,
             //                   window_attributes_mask);
            // gtk_widget_register_window(widget, viewWindow);
            // gtk_widget_set_window(widget, viewWindow);
            // gdk_window_show(viewWindow);

            // CustomRender *customRender= std::make_unique<CustomRender>(self->width, self->height);//, texture_registrar_, m_hWnd);
            //GError *error = NULL;
        //    self->context = gdk_window_create_gl_context(self->window, &error);
            CustomRender *customRender = new CustomRender(self->width,self->height,self->texture_registrar, self->window);//context);
            self->render=customRender;
            //self->window);//std::make_unique<CustomRender>(width, height);//, texture_registrar_, m_hWnd);

            int64_t textureID = customRender->texture_id();

            printf(".... textureid %ld\n",textureID);
            //g_autoptr(FlValue)  textureID = customRender->texture_id();
           // self->renders_=new std::map<int64_t, std::unique_ptr<CustomRender>>();//std::map<int, std::string>();
         //   self->renders_->try_emplace( textureID, std::move(customRender) );

            // try gtk opengl example https://github.com/aklomp/gtk3-opengl/blob/master/gui.c
        //    gtk_gl_area_set_has_depth_buffer(GTK_WIDGET(self->fl_view), TRUE);

            //  renders_[textureID]=customRender;
            // GLenn window equivalent to mhwnd
            //window = nullptr;
            /*GError *error = NULL;
            self->context = gdk_window_create_gl_context(self->window, &error);

            gdk_gl_context_make_current(self->context);

            glGenTextures(1, &self->texture_name);
            glBindTexture(GL_TEXTURE_2D, self->texture_name);


            self->myTexture = fl_my_texture_gl_new(GL_TEXTURE_2D, self->texture_name, self->width, self->height);
            self->texture = FL_TEXTURE(self->myTexture);
            fl_texture_registrar_register_texture(self->texture_registrar, self->texture);
            fl_texture_registrar_mark_texture_frame_available(self->texture_registrar, self->texture);

            gdk_gl_context_clear_current();

            // glenn defined in OpenglPluginContext ctx_f  in common.h
            ctx_f.context = self->context;
            ctx_f.texture_name = self->texture_name;
            ctx_f.texture_registrar = self->texture_registrar;
            ctx_f.myTexture = self->myTexture;
            ctx_f.texture = self->texture;
            ctx_f.width = self->width;
            ctx_f.height = self->height;

            // glenn found in ffi.h - foreign interface
            createRenderer(&ctx_f);
            g_autoptr(FlValue) textureId =
                  fl_value_new_int(fl_texture_get_id(FL_TEXTURE(self->texture)));*/
            g_autoptr(FlValue) data = fl_value_new_map();
            // check out https://gitlab.novinparva.com/medga/flutter/-/blob/3.16.9/examples/texture/linux/my_application.cc
            fl_value_set(data, fl_value_new_string("textureId"), fl_value_new_int(textureID));//fl_value_new_int(reinterpret_cast<int64_t>(self->texture)));
			//g_autoptr(FlValue) result =
			//	fl_value_new_int(reinterpret_cast<int64_t>(self->texture));
          //  main2(self,self->width, self->height);
        /*    GtkTextBuffer *buffer;

            // view = gtk_text_view_new ();

            GtkWidget *view= GTK_WIDGET(self->fl_view);
            buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

            gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);*/
        /*    GdkRGBA color;
            color.red = 0;
            color.green = 1;
            color.blue = 0;
            color.alpha = 1;
            gtk_widget_override_background_color (GTK_WIDGET(self->fl_view), GTK_STATE_FLAG_NORMAL, &color);

        GtkWidget *view;
            GtkTextBuffer *buffer;

            view = gtk_text_view_new ();

            buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

            gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);*/
          /*  cairo_t *cr;

            cr = cairo_create (surface);

            cairo_set_source_rgb (cr, 1, 1, 1);
            cairo_paint (cr);

            cairo_destroy (cr);*/
            response = FL_METHOD_RESPONSE(fl_method_success_response_new(data));//result));
		}

	} // end createSurface
    else if (strcmp(method, "getEgl") == 0)  //createSurface
    {
    //    mutex_.lock();
        printf(".... getegl\n");
     //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //XInitThreads();
        /*
         *   ] [xcb] Unknown sequence number while processing queue
[        ] [xcb] You called XInitThreads, this is not your fault
[        ] [xcb] Aborting, sorry about that.
[        ] secondtemple: ../../src/xcb_io.c:278: poll_for_event: Assertion `!xcb_xlib_threads_sequence_lost' failed.
         */
      /*  std::ofstream myfile;
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        myfile.open("/home/glennlinde/secondtemple.log",std::ios_base::app);
        std::cout << myfile.is_open() << std::endl;
        myfile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << "getegl\n";
        myfile.close();
*/
     //   mylog("getegl");
       // FlValue *t = fl_value_lookup_string(args, "textureId");
       // int64_t textureId = fl_value_get_int(t);
     /*   auto render = self->renders_->find(textureId);
        if(render != self->renders_->end()) {
            printf("voooti\n");

        }*/
      /*  myfile.open("/home/glennlinde/secondtemple.log",std::ios_base::app);
        std::cout << myfile.is_open() << std::endl;
        myfile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << "getegl textureid\n";
        myfile.close();*/
      //  mylog("getegl textureid");

       // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        //    g_autoptr(FlValue) fl_vector =render->second->getEgls();
        g_autoptr(FlValue) fl_vector =self->render->getEgls();
        printf(".... getegl render getegls\n");
      //  mylog("getegl render getegls");

     /*  g_autoptr(FlValue) fl_vector = fl_value_new_list();;//render->second->getEgls();// fl_value_new_list(.);
        fl_value_append(fl_vector,  fl_value_new_int(0));
        fl_value_append(fl_vector,  fl_value_new_int(0));
        fl_value_append(fl_vector,  fl_value_new_int(reinterpret_cast<int64_t>(self->render->eglEnv.context_)));//self->context)));
        fl_value_append(fl_vector,  fl_value_new_int(0));
        fl_value_append(fl_vector,  fl_value_new_int(0));
        fl_value_append(fl_vector,  fl_value_new_int(reinterpret_cast<int64_t>(self->render->dartEglEnv.context_)));//self->context)));
      */
      //  gdk_gl_context_clear_current();
        response = FL_METHOD_RESPONSE(fl_method_success_response_new(fl_vector));
      // gdk_gl_context_make_current(self->render->dartEglEnv.context_);
     //  makeCurrent( self->render->dartEglEnv.context_);
        //mylog("getegl resonse done");
       // mutex_.unlock();

    //    printf(".... done getegl \n");//,render->second->width);

       // response = FL_METHOD_RESPONSE(fl_method_success_response_new(fl_vectoru));
    }
    else if (strcmp(method, "updateTexture") == 0)  //createSurface
    {
       // gdk_window_show (self->window);
        printf(".... update texture %d\n",self->width);//renders_.size());

        int textureId = fl_value_get_int(fl_value_lookup_string(args, "textureId"));
        int sourceTexture  = fl_value_get_int(fl_value_lookup_string(args, "sourceTexture"));
    //    printf(".... update texture vals %ld %ld\n",textureId, sourceTexture);
       // self->renders_->begin();
       /* auto render = self->renders_->find(textureId);

        if(render != self->renders_->end()) {
             printf("vooot\n");
        }*/
       // CustomRender *arender=render->second.get();

       // printf("xxxxx %d\n",arender->width);//render->second->width);//arender);//self->renders_->size());//render);
    //   printf(".... update texture width %d\n",render->second->width);
        int data = self->render->updateTexture( sourceTexture );
     //   int data = render->second->updateTexture( sourceTexture );
       // mainFBO(self, self->width, self->height);

        // copy mainFBO3 in test.cpp
    //    self->texture_registrar->MarkTextureFrameAvailable(textureId);
     //   gdk_gl_context_make_current(self->context); Already been called
      /*  GLuint vs, p, vao, tex, fbo, lUseTex;
        p=glCreateProgram();
        //cs(p,GL_VERTEX_SHADER,vertex_shader0);
        //cs(p,GL_FRAGMENT_SHADER,fragment_shader0);
      //  glLinkProgram(p);
        glUseProgram(p);
        //GLuint _positionSlot = glGetAttribLocation(p, "position");

        GLuint _positionSlot = GLuint(glGetAttribLocation(p, "position"));
        GLuint _textureSlot = GLuint(glGetAttribLocation(p, "textureCoords"));

        GLuint _texture0Uniform = GLuint(glGetUniformLocation(p, "Texture0"));

        glActiveTexture(GLenum(GL_TEXTURE8));
        glBindTexture(GLenum(GL_TEXTURE_2D), sourceTexture);
        glUniform1i(GLint(_texture0Uniform), 8);

        // !! put the vertext buffer in renderhelp in here
        //glBindBuffer(GLenum(GL_ARRAY_BUFFER), vertexBuffer_);

        lUseTex=glGetUniformLocation(p,"useTex");

        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        // glGenTextures(1,&self->texture_name);
        glVertexAttribPointer(_positionSlot, 3, GLenum(GL_FLOAT), GLboolean(GL_FALSE), 5 * sizeof(float), (GLvoid*)0);

        // 设置顶点数据
        glEnableVertexAttribArray(_positionSlot);

        glVertexAttribPointer(_textureSlot, 2, GLenum(GL_FLOAT), GLboolean(GL_FALSE), 5 * sizeof(float), (const GLvoid*)(3*sizeof(float)));

        glEnableVertexAttribArray(_textureSlot);

        glDrawArrays(GLenum(GL_TRIANGLE_STRIP), 0, 4);


        glDeleteVertexArrays(1, &vao);

       // printf("%d\n",textureId);//self->width);
        glBindTexture(GL_TEXTURE_2D, sourceTexture);//self->texture_name);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->width, self->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glGenFramebuffers(1,&fbo);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, self->texture_name, 0);


        // while (!glfwWindowShouldClose(win)) {
        // 	int w,h;
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glViewport(0,0,self->width, self->height);
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform1i(lUseTex,0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        // glfwGetFramebufferSize(win,&w,&h);
        glViewport(0,0,self->width, self->height);
        glUniform1i(lUseTex,1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // 	glfwSwapBuffers(win);
        // 	glfwPollEvents();
        // }


        fl_texture_registrar_mark_texture_frame_available(self->texture_registrar,
                                                          self->texture);*/
        //gdk_gl_context_clear_current();
        response = FL_METHOD_RESPONSE(fl_method_success_response_new(fl_value_new_int(data)));

    }    else if (strcmp(method, "dispose") == 0)
    {
        printf(".... dispose in self\n");
        // response = FL_METHOD_RESPONSE(fl_method_success_response_new(result));
        //fl_texture_registrar_unregister_texture(self->texture_registrar, self->texture);
        // g_autoptr(FlValue) result = fl_value_new_int(-1);
         g_autoptr(FlValue) result = fl_value_new_null();
        response = FL_METHOD_RESPONSE(fl_method_success_response_new(result));

    }
    else
	{
		response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
	}

    //mylog("call respond");
	fl_method_call_respond(method_call, response, nullptr);
    printf(".... call respond out\n");
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
    printf(".... method_call_cb\n");
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