package xiaotongren.wifi.actvity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


import xiaotongren.wifi.R;

public class SetPortActivity extends AppCompatActivity  implements View.OnClickListener {


    EditText editText_set_port_addr ;
    Button button_set_debug_addr ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set_port);

        setTitle("远程地址");


        editText_set_port_addr=(EditText)findViewById(R.id.editText_set_port_addr);

        button_set_debug_addr=(Button)findViewById(R.id.button_set_port_confirm);

        button_set_debug_addr.setOnClickListener(this);

        set_debug_addr();





    }


    private  void set_debug_addr()
    {
        String url = read_from_local("debug_addr","remote_debug_addr");

        if(url.equals("0"))
        {
//            Toast.makeText(getApplicationContext(),"null debug addr",Toast.LENGTH_SHORT).show();
        }
        else
        {
            editText_set_port_addr.setText(url);

//            Toast.makeText(getApplicationContext(),url,Toast.LENGTH_SHORT).show();
        }
    }



    public String read_from_local(String name ,String key)
    {
        try
        {
            SharedPreferences read = getSharedPreferences(name, MODE_WORLD_READABLE);
            String value = read.getString(key, "0");
            return value ;
        }catch (Exception ex)
        {
            Log.e("save_data_to_local","fail on read." +ex.getMessage());
            Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
            return "";
        }


    }



    @Override
    public void onClick(View v) {
        switch (v.getId()) {

            case R.id.button_set_port_confirm:

                new AlertDialog.Builder(this)
                        //   .setIcon(android.R.drawable.edit_text)
//                        .setTitle("账户更改提示")
//                        .setTitle(" ")
                        .setMessage("确定输入了正确的调试地址吗？")
                        .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {

                            }
                        })
                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int whichButton) {

                                String set_port_addr = editText_set_port_addr.getText().toString().trim();

                                save_to_local("debug_addr","remote_debug_addr",set_port_addr);

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
            Log.e("save_data_to_local","fail on save." +ex.getMessage());
            Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
            return;
        }
    }
}
