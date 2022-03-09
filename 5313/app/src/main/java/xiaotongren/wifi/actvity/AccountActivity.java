package xiaotongren.wifi.actvity;

import android.app.AlertDialog;
import android.content.DialogInterface;
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


public class AccountActivity extends AppCompatActivity implements View.OnClickListener {



    Button button_login ;
    EditText editText_user ;
    EditText editText_passwd ;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_account);


        button_login = (Button)findViewById(R.id.button_change_account_confirm) ;
        editText_user = (EditText)findViewById(R.id.editText_change_account_user);
        editText_passwd = (EditText)findViewById(R.id.editText_change_account_passwd);

        button_login.setOnClickListener(this);

    }



    @Override
    public void onClick(View v) {
        switch (v.getId()) {

            case R.id.button_change_account_confirm:




                new AlertDialog.Builder(this)
                        //   .setIcon(android.R.drawable.edit_text)
                        .setTitle("账户更改提示")
//                        .setTitle(" ")
                        .setMessage("确定对帐户做出更改吗？")
                        .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {

                            }
                        })
                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int whichButton) {

                                String change_user = editText_user.getText().toString().trim();
                                String change_passwd = editText_passwd.getText().toString().trim();

                                save_to_local("login","user",change_user);
                                save_to_local("login","passwd",change_passwd);

                                finish();


                            }
                        }).show();



                break;


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
