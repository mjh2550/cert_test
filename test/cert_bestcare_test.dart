import 'package:flutter_test/flutter_test.dart';
import 'package:cert_bestcare/cert_bestcare.dart';
import 'package:cert_bestcare/cert_bestcare_platform_interface.dart';
import 'package:cert_bestcare/cert_bestcare_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockCertBestcarePlatform
    with MockPlatformInterfaceMixin
    implements CertBestcarePlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final CertBestcarePlatform initialPlatform = CertBestcarePlatform.instance;

  test('$MethodChannelCertBestcare is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelCertBestcare>());
  });

  test('getPlatformVersion', () async {
    CertBestcare certBestcarePlugin = CertBestcare();
    MockCertBestcarePlatform fakePlatform = MockCertBestcarePlatform();
    CertBestcarePlatform.instance = fakePlatform;

    expect(await certBestcarePlugin.getPlatformVersion(), '42');
  });
}
