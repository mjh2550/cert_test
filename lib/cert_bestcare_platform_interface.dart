import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'cert_bestcare_method_channel.dart';

abstract class CertBestcarePlatform extends PlatformInterface {
  /// Constructs a CertBestcarePlatform.
  CertBestcarePlatform() : super(token: _token);

  static final Object _token = Object();

  static CertBestcarePlatform _instance = MethodChannelCertBestcare();

  /// The default instance of [CertBestcarePlatform] to use.
  ///
  /// Defaults to [MethodChannelCertBestcare].
  static CertBestcarePlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [CertBestcarePlatform] when
  /// they register themselves.
  static set instance(CertBestcarePlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  Future<int?> libInitialize() {
    throw UnimplementedError('libInitialize() has not been implemented.');
  }

  Future<bool?> setServiceUrl(String url) {
    throw UnimplementedError('setServiceUrl() has not been implemented.');
  }

  Future<String?> getCertification(String userId) {
    throw UnimplementedError('getCertification() has not been implemented.');
  }

  Future<List<Object?>?> getUserCertificateListWithGpki() {
    throw UnimplementedError('getUserCertificateListWithGpki() has not been implemented.');
  }
}
