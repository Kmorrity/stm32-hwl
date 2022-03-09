package xiaotongren.wifi.actvity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.KeyEvent;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;


import xiaotongren.wifi.R;
import xiaotongren.wifi.common.MyWebChromeClient;
import xiaotongren.wifi.esptouch.demo_activity.EsptouchDemoActivity;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {

    private static  final  boolean IsDebug = true ;
    private static final String TAG = "MainActivity";

    WebView webView_main ;
    Toolbar toolbar;




    @Override
    protected void onCreate(Bundle savedInstanceState) {

        requestWindowFeature(Window.FEATURE_NO_TITLE);
//        if (getSupportActionBar() != null){
//            getSupportActionBar().hide();
//        }

//        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
//        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);


        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//
//        toolbar = (Toolbar) findViewById(R.id.toolbar);
//        setSupportActionBar(toolbar);

//        fab = (FloatingActionButton) findViewById(R.id.fab);
//        fab.setOnClickListener(this);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);

//        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
//                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
//        drawer.setDrawerListener(toggle);
//        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);








        webView_main = (WebView)findViewById(R.id.webview_main);


        webView_main.getSettings().setJavaScriptEnabled(true);
        webView_main.getSettings().setJavaScriptCanOpenWindowsAutomatically(true);
        webView_main.getSettings().setSupportMultipleWindows(true);
        webView_main.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);  //no cache the resource
//        webView_main.getSettings().setCacheMode(WebSettings.LOAD_DEFAULT);

        webView_main.getSettings().setDomStorageEnabled(true); //local storage

//        //设置可自由缩放网页
//        webView_help.getSettings().setSupportZoom(true);
//        webView_help.getSettings().setBuiltInZoomControls(true);

        webView_main.setWebViewClient(new WebViewClient());
        webView_main.setWebChromeClient(new MyWebChromeClient());
        //  webView_help.loadUrl("http://laomao.sc2yun.com/laomao/web/help.html");
        webView_main.loadUrl(getResources().getString(R.string.main_webview_url));




//        webView_main.loadUrl("http://192.168.1.166/web/html/sensor_monitor.html");
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();

        }

        super.onBackPressed();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }


    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if ((keyCode == KeyEvent.KEYCODE_BACK)) {
//            if((System.currentTimeMillis()-exitTime) > 2000){
//                Toast.makeText(getApplicationContext(), "再按一次退出程序", Toast.LENGTH_SHORT).show();
//                exitTime = System.currentTimeMillis();
//            } else {
//                finish();
//                System.exit(0);
//            }


            new AlertDialog.Builder(this)
                    //   .setIcon(android.R.drawable.edit_text)
                    // .setTitle("  请注意")
                    .setTitle(" ")
                    .setMessage("确定要退出吗？")
                    .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                        }
                    })
                    .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int whichButton) {
                            finish();
                        }
                    }).show();
            return false;


        }else {
            return super.onKeyDown(keyCode, event);
        }

    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_link_debug) {


            String url = read_from_local("debug_addr","remote_debug_addr");

            if(url.equals("0"))
            {
                Toast.makeText(getApplicationContext(),"null debug addr",Toast.LENGTH_SHORT).show();
            }
            else
            {
                webView_main.loadUrl(url);

                Toast.makeText(getApplicationContext(),url,Toast.LENGTH_SHORT).show();
            }

            return true;
        }

        if (id == R.id.action_link_default) {

            webView_main.loadUrl(getResources().getString(R.string.main_webview_url));

            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.nav_port) {

            Intent intent = new Intent(this, SetPortActivity.class);
            startActivity(intent);
        }

        else if (id == R.id.nav_smartlink) {
            Intent intent = new Intent(this,EsptouchDemoActivity.class);
            startActivity(intent);

        }
//        else if (id == R.id.nav_send) {
//
//        }
//        else if (id == R.id.nav_debug) {
//
//
//            Intent intent = new Intent(this,DebugActivity.class);
//            startActivity(intent);
//
//        }
//        else if (id == R.id.nav_acount) {
//
//
//            Intent intent = new Intent(this,AccountActivity.class);
//            startActivity(intent);
//
//        }

//        else if (id == R.id.nav_help) {
////
////            Intent intent = new Intent(this,HelpActivity.class);
////            startActivity(intent);
//
//        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }



    @Override
    protected void onStop() {

        super.onStop();
    }



    @Override
    protected void onDestroy() {


        super.onDestroy();
    }


    public String read_from_local(String name ,String key)
    {
        SharedPreferences read = getSharedPreferences(name, MODE_WORLD_READABLE);
        String value = read.getString(key, "0");
        return value ;
    }



}
