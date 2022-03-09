package xiaotongren.wifi.actvity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import xiaotongren.wifi.R;

public class LoginActivity extends AppCompatActivity implements View.OnClickListener{


    Button button_login ;
    EditText editText_user ;
    EditText editText_passwd ;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);


        button_login = (Button)findViewById(R.id.button_login) ;
        editText_user = (EditText)findViewById(R.id.editText_user);
        editText_passwd = (EditText)findViewById(R.id.editText_passwd);

        button_login.setOnClickListener(this);


        String is_first_launch = read_from_local("login","first");
        if(is_first_launch.equals("0"))
        {

            save_to_local("login","user","admin");
            save_to_local("login","passwd","admin");
            save_to_local("login","first","1");

        }
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()) {

            case R.id.button_login:

                if(check_passwd())
                {
                    Intent next = new Intent(LoginActivity.this , MainActivity.class);

                    String deault_main_webview_url = getResources().getString(R.string.main_webview_url);

                    save_to_local("debug_addr","remote_debug_addr",deault_main_webview_url);
                    startActivity(next);
                }
                else
                {
                    Toast.makeText(this, R.string.login_fail, Toast.LENGTH_SHORT).show();
                    Intent next = new Intent(LoginActivity.this , MainActivity.class);
                    startActivity(next);
                }

                break;

            default:

                break;
        }
    }


    private boolean check_passwd()
    {


        String str_user = read_from_local("login","user");
        String str_passwd = read_from_local("login","passwd");


        if (editText_user.getText().toString().trim().equals(str_user)
                && editText_passwd.getText().toString().trim().equals(str_passwd))

        {
            return  true ;
        }
        else {
            return false;
        }
    }





    public void save_to_local(String name ,String key ,String value)
    {
        try {
            SharedPreferences.Editor editor = getSharedPreferences(name, MODE_WORLD_WRITEABLE).edit();
            editor.putString(key, value);
            editor.commit();//提交修改

        }catch (Exception ex)
        {
            Log.e("save_data_to_local","fail on save");
            Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
            return;
        }
    }

    public String read_from_local(String name ,String key)
    {
        SharedPreferences read = getSharedPreferences(name, MODE_WORLD_READABLE);
        String value = read.getString(key, "0");
        return value ;
    }
}
