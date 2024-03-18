
import 'cert_bestcare_platform_interface.dart';

class CertBestcare {
  Future<String?> getPlatformVersion() {
    return CertBestcarePlatform.instance.getPlatformVersion();
  }
}
