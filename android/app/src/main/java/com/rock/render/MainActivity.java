package com.rock.render;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.widget.TextView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class AliceGLSurfaceViewRenderer implements GLSurfaceView.Renderer{
    public void onSurfaceCreated(GL10 gl, EGLConfig var2){
        MainActivity.Instance().Init(MainActivity.Instance().getAssets());
    }
    public void onSurfaceChanged(GL10 gl, int width, int height){
        MainActivity.Instance().OnViewportChanged(width,height);
    }
    public void onDrawFrame(GL10 gl){
        MainActivity.Instance().Render();
    }
}
class AliceGLSurfaceView extends GLSurfaceView {
    GLSurfaceView.Renderer mRenderer;
    public AliceGLSurfaceView(Context context){
        super(context);
        setEGLContextClientVersion(2);
        mRenderer=new AliceGLSurfaceViewRenderer();
        setRenderer(mRenderer);
    }
}

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("Alices");
    }

    static MainActivity mSelf;
    AliceGLSurfaceView mGLView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mSelf=this;
        mGLView=new AliceGLSurfaceView(getApplication());
        setContentView(mGLView);
    }
    public static MainActivity Instance(){
        return mSelf;
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void Init(AssetManager am);
    public native void OnViewportChanged(int width,int height);
    public native void Render();
}
