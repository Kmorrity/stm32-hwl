package xiaotongren.wifi.actvity;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceResponse;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import xiaotongren.wifi.R;
import xiaotongren.wifi.common.MyWebChromeClient;

public class HelpActivity extends AppCompatActivity {

    WebView webView_help ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_help);


        webView_help = (WebView)findViewById(R.id.webview_help);


        webView_help.getSettings().setJavaScriptEnabled(true);
        webView_help.getSettings().setJavaScriptCanOpenWindowsAutomatically(true);
        webView_help.getSettings().setSupportMultipleWindows(true);
//        webView_help.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);
        webView_help.getSettings().setCacheMode(WebSettings.LOAD_DEFAULT);

//        //设置可自由缩放网页
//        webView_help.getSettings().setSupportZoom(true);
//        webView_help.getSettings().setBuiltInZoomControls(true);

        webView_help.setWebViewClient(new WebViewClient());
        webView_help.setWebChromeClient(new MyWebChromeClient());
      //  webView_help.loadUrl("http://laomao.sc2yun.com/laomao/web/help.html");
      //  webView_help.loadUrl("file:///android_asset/html/index.html");
       // webView_help.loadUrl("file:///android_asset/line/index.html");
        webView_help.loadUrl("file:///android_asset/help/help.html");
    }
}
