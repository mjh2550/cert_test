
import 'cert_bestcare_platform_interface.dart';

class CertBestcare {
  Future<String?> getPlatformVersion() {
    return CertBestcarePlatform.instance.getPlatformVersion();
  }

  Future<int?> libInitialize() {
    return CertBestcarePlatform.instance.libInitialize();
  }

  Future<bool?> setServiceUrl(String url) async {
    return CertBestcarePlatform.instance.setServiceUrl(url);
  }

  Future<String?> getCertification(String userId) async {
    return CertBestcarePlatform.instance.getCertification(userId);
  }

  Future<List<Object?>?> getUserCertificateListWithGpki() async {
    return CertBestcarePlatform.instance
        .getUserCertificateListWithGpki();
  }
}
