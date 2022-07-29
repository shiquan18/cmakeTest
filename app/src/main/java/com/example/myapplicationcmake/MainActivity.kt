package com.example.myapplicationcmake

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.myapplicationcmake.databinding.ActivityMainBinding
import java.util.*

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
//        binding.sampleText.text = stringFromJNI3()
//        binding.sampleText.text = accessField()
        binding.sampleText.text = "${accessStaticField()}"
        accessMethod()
    }

    external fun stringFromJNI(): String
    external fun stringFromJNI2(): String
    external fun stringFromJNI3(): String

    private var key: String = "MainActivity's key"
    external fun accessField(): String//修改key字段

    private var count: Int = 11
    external fun accessStaticField(): Int//修改 count 字段


    external fun accessMethod()

    fun genRandomInt(max: Int): Int {
        val random = Random()
        showLog("$max")
        return random.nextInt(max)
    }

    companion object {
        // Used to load the 'myapplicationcmake' library on application startup.
        init {
            System.loadLibrary("myapplicationcmake")
        }
    }

    fun showLog(msg: String) {
        Log.e("MainActivity", msg)
    }
}