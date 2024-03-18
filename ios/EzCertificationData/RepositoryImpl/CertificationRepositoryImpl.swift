//
//  CertificationRepositoryImpl.swift
//  EzConsentData
//
//  Created by Jinho Lee on 2022/10/02.
//

import EzConsentDomain
import Foundation
import RxSwift

public class CertificationRepositoryImpl: CertificationRepository {
    let keySharp: KeySharpAdaptor

    // MARK: Initialize

    public init(with serviceUrl: String) {
        let keySharp = KeySharpAdaptor.shared() as! KeySharpAdaptor
        keySharp.serviceUrl = serviceUrl
        self.keySharp = keySharp
    }

    // MARK: Public Method

    public func download(with userId: String) throws -> Int {
        try keySharp.download(with: userId)
        return keySharp.certIndex
    }

    public func sign(with password: String, message: String) throws -> String {
        return try keySharp.sign(with: password, message: message)
    }

    public func removeAll() {
        keySharp.removeAll()
    }
}
