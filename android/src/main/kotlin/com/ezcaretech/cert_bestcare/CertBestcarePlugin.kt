package com.ezcaretech.cert_bestcare


import android.app.Activity
import android.content.Context
// import androidx.annotation.NonNull

import com.ezcaretech.ezcertificationdata.cert.KSWCertManager
import com.isolutec.icertmanager.iCertClient
import com.lumensoft.ks.KSCertificate
import com.lumensoft.ks.KSCertificateLoader
import com.lumensoft.ks.KSCertificateManager
import com.lumensoft.ks.KSException

import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.embedding.engine.plugins.activity.ActivityAware
import io.flutter.embedding.engine.plugins.activity.ActivityPluginBinding;
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result

import java.util.*

import kotlin.concurrent.thread

/** CertBestcarePlugin */
class CertBestcarePlugin: FlutterPlugin, MethodCallHandler {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  private lateinit var channel : MethodChannel
  private lateinit var context: Context
  private lateinit var activity: Activity
  private lateinit var iCertClient: iCertClient

  init {
    iCertClient = iCertClient()
  }

  override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "cert_bestcare")
    channel.setMethodCallHandler(this)
    context = flutterPluginBinding.applicationContext
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    when (call.method) {
        "getPlatformVersion" -> {
          result.success("Android ${android.os.Build.VERSION.RELEASE}")
        }
        "libInitialize" -> {
            try {
                result.success(KSCertificateManager.libInitialize())
            } catch (e:Exception) {
                result.error("KSException", e.message, e.stackTrace)
            }

        }
        "setServiceUrl" -> {
          iCertClient.SetServiceUrl(call.argument("url"))
          result.success(true)
        }
        "getCertification" -> {
          thread {
            result.success(iCertClient.GetCertification(call.argument("userId")))
          }
        }
        "getUserCertificateListWithGpki" -> {
          try {
            result.success(getCertifications())
          } catch (ex: KSException) {
            result.error("KSException", ex.message, ex.stackTrace)
          }
        }
        else -> {
          result.notImplemented()
        }
    }
  }

  override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }

  private fun getCertifications(): Vector<KSCertificate?>? {
    var userCerts: Vector<KSCertificate?>?
    userCerts = KSCertificateLoader.getUserCertificateListWithGpki(context) as Vector<KSCertificate?>?
    userCerts = KSCertificateLoader.FilterByExpiredTime(userCerts) as Vector<KSCertificate?>?
    return userCerts
  }
}
