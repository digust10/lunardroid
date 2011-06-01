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
package br.com.thecodebakers.lua;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class InvokeLua extends Activity {
    
    static {
    	System.loadLibrary("callLua");
    }
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        String saida = execLuaScript("function f (x, y) "
        							+ " return (x * y)"
        							+ " end");
        
        TextView txt = (TextView) this.findViewById(R.id.txtsaida);
        txt.setText(saida);
    }
    
    /**
     * Método nativo para invocar o interpretador LUA passando um programa dentro 
     * dentro de um String Java
     * @param codigoLua Código-fonte em LUA, separado por "\n"
     * @return Saida do Interpretador LUA
     */
    private native String execLuaScript(String codigoLua);
}