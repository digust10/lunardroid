/*
 * Copyright (C) 2011 The Code Bakers
 * Authors: Cleuton Sampaio e Francisco Rodrigues
 * e-mail: thecodebakers@gmail.com
 * Project: http://code.google.com/p/lunardroid01/
 * Site: http://thecodebakers.blogspot.com
 *
 * Licensed under the GNU GPL, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://gplv3.fsf.org/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * @author Cleuton Sampaio e Francisco Rogrigues - thecodebakers@gmail.com
 */

// Includes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <jni.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <callLua.h>
#include <android/log.h>

jstring
Java_br_com_thecodebakers_lua_InvokeLua_execLuaScript( JNIEnv* env,
                                                            jobject objThis,
                                                            jstring progString) {
      char buf[10000];
      const char *str;
      int error;

      lua_State *L = lua_open();   /* opens Lua */
      luaopen_base(L);             /* opens the basic library */
      luaopen_table(L);            /* opens the table library */
      //luaopen_io(L);               /* opens the I/O library */
      luaopen_string(L);           /* opens the string lib. */
      luaopen_math(L);             /* opens the math lib. */

      str = (*env)->GetStringUTFChars(env, progString, NULL);
      strcpy (buf, str);

      if (str == NULL) {
              return NULL; 
      }

      (*env)->ReleaseStringUTFChars(env, progString, str);

      error = luaL_loadstring(L, buf)  || lua_pcall(L, 0, 0, 0);

      if (error) {
            __android_log_print(ANDROID_LOG_INFO, "@@@@@@Erro no LOadBuffer  ", "%s", lua_tostring(L, -1));
      }

      lua_getglobal(L, "f"); 
      if(!lua_isfunction(L,-1))
      {
         __android_log_print(ANDROID_LOG_INFO, "@@@@@@Nao e funcao  ", "%s", NULL);
      }
      else {
         __android_log_print(ANDROID_LOG_INFO, "@@@@@@Eh funcao  ", "%s", NULL);
      }
      lua_pushnumber(L, 110.0);  
      lua_pushnumber(L, 2.0);   
    
      if (lua_pcall(L, 2, 1, 0) != 0) {
      __android_log_print(ANDROID_LOG_INFO, "@@@@@@error running function  ", "%s", lua_tostring(L, -1));
      }

      if (!lua_isnumber(L, -1))
        __android_log_print(ANDROID_LOG_INFO, "@@@@@@error deve retornar um valor  ", "%s", lua_tostring(L, -1));

      double z = lua_tonumber(L, -1);
      __android_log_print(ANDROID_LOG_INFO, "@@@@@@Valor do z  ", "%f", z);

      lua_pop(L, 1);  

      char saida[1024];
      sprintf(saida, "%f", z);
      lua_close(L);
      return (*env)->NewStringUTF(env,saida);

	
}

