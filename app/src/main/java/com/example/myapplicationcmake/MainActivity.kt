package com.example.myapplicationcmake

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.example.myapplicationcmake.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI2()
    }

    /**

     */
    external fun stringFromJNI(): String
    external fun stringFromJNI2(): String

    companion object {
        // Used to load the 'myapplicationcmake' library on application startup.
        init {
            System.loadLibrary("myapplicationcmake")
        }
    }
}