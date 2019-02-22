#include "Module.h"
#include "IOCDM.h"
#include "open_cdm.h"

namespace WPEFramework {

    // -------------------------------------------------------------------------------------------
    // STUB
    // -------------------------------------------------------------------------------------------

    //
    // OCDM::IAccessorOCDM interface stub definitions (interface/ICDM.h)
    //
    ProxyStub::MethodHandler AccesorOCDMStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual OCDM_RESULT IsTypeSupported(
            //     const std::string keySystem,
            //     const std::string mimeType) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            std::string keySystem = parameters.Text();
            std::string mimeType = parameters.Text();

            response.Number(message->Parameters().Implementation<OCDM::IAccessorOCDM>()->IsTypeSupported(keySystem, mimeType));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // static OCDM::ISession* Session(
            //     const std::string sessionId) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            std::string sessionId = parameters.Text();

            response.Number<OCDM::ISession*> (message->Parameters().Implementation<OCDM::IAccessorOCDM>()->Session(sessionId));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // static OCDM::ISession* Session(
            //     const uint8 keyId[], const uint8_t length) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            const uint8_t* keyData;
            uint8_t keyDataLength = parameters.LockBuffer<uint8_t>(keyData);

            response.Number<OCDM::ISession*> (message->Parameters().Implementation<OCDM::IAccessorOCDM>()->Session(keyData, keyDataLength));

            parameters.UnlockBuffer(keyDataLength);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Create a MediaKeySession using the supplied init data and CDM data.
            // virtual OCDM_RESULT CreateSession(
            //   const string keySystem,
            //   const int32_t licenseType,
            //   const string initDataType,
            //   const uint8_t* initData,
            //   const uint16_t initDataLength,
            //   const uint8_t* CDMData,
            //   const uint16_t CDMDataLength,
            //   ISession::ICallback* callback,
            //   std::string& sessionId,
            //   std::string& bufferId,
            //   ISession*& session) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            string keySystem = parameters.Text();
            int32_t licenseType = parameters.Number<int32_t>();
            string initDataType = parameters.Text();

            const uint8_t* initData;
            uint16_t initDataLength = parameters.LockBuffer<uint16_t>(initData);
            parameters.UnlockBuffer(initDataLength);

            const uint8_t* CDMData;
            uint16_t CDMDataLength = parameters.LockBuffer<uint16_t>(CDMData);
            parameters.UnlockBuffer(CDMDataLength);

            OCDM::ISession::ICallback* implementation = parameters.Number<OCDM::ISession::ICallback*>();
            OCDM::ISession::ICallback* proxy = nullptr;

            if (implementation != nullptr) {
                proxy = RPC::Administrator::Instance().CreateProxy<OCDM::ISession::ICallback>(channel,
                    implementation,
                    true, false);

                ASSERT((proxy != nullptr) && "Failed to create proxy");
            }

            string sessionId;
            OCDM::ISession* result = nullptr;

            response.Number(message->Parameters().Implementation<OCDM::IAccessorOCDM>()->CreateSession(
                keySystem,
                licenseType, 
                initDataType,
                initData,
                initDataLength,
                CDMData,
                CDMDataLength,
                proxy,
                sessionId,
                result));

            response.Text(sessionId);
            response.Number<OCDM::ISession*>(result);

            if ( (proxy != nullptr) && (proxy->Release() != Core::ERROR_NONE)) {
                TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Set Server Certificate
            // virtual OCDM_RESULT SetServerCertificate(
            //     const string keySystem,
            //     const uint8_t* serverCertificate,
            //     const uint16_t serverCertificateLength) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            string keySystem = parameters.Text();
            const uint8_t* serverCertificate;
            uint16_t serverCertificateLength = parameters.LockBuffer<uint16_t>(serverCertificate);

            response.Number(message->Parameters().Implementation<OCDM::IAccessorOCDM>()->SetServerCertificate(
                keySystem,
                serverCertificate,
                serverCertificateLength));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // 
            // virtual void Register(OCDM::IAccessorOCDM::INotification* callback) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            OCDM::IAccessorOCDM::INotification* implementation = parameters.Number<OCDM::IAccessorOCDM::INotification*>();
            OCDM::IAccessorOCDM::INotification* proxy = nullptr;

            if (implementation != nullptr) {
                proxy = RPC::Administrator::Instance().CreateProxy<OCDM::IAccessorOCDM::INotification>(channel,
                    implementation,
                    true, false);

                ASSERT((proxy != nullptr) && "Failed to create proxy");
            }

            message->Parameters().Implementation<OCDM::IAccessorOCDM>()->Register(proxy);

            if (proxy != nullptr) {
                proxy->Release();
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // 
            // virtual void Unregister(OCDM::IAccessorOCDM::INotificationISession::IKeyCallback* callback) = 0;
            //
            RPC::Data::Frame::Reader reader(message->Parameters().Reader());

            // Need to find the proxy that goes with the given implementation..
            OCDM::IAccessorOCDM::INotification* stub = reader.Number<OCDM::IAccessorOCDM::INotification*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            OCDM::IAccessorOCDM::INotification* proxy = RPC::Administrator::Instance().FindProxy<OCDM::IAccessorOCDM::INotification>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Coud not find stub for OCDM::IAccessorOCDM::INotification: %p"), stub);
            } else {
                message->Parameters().Implementation<OCDM::IAccessorOCDM>()->Unregister(proxy);
            }
        },
 
        nullptr
    };

    ProxyStub::MethodHandler AccesorOCDMExtStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual time_t GetDrmSystemTime() const = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::IAccessorOCDMExt>()->GetDrmSystemTime());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual OCDM_RESULT CreateSessionExt(
            //    uint32_t sessionId,
            //    const char contentId[],
            //    uint32_t contentIdLength,
            //    LicenseTypeExt licenseType,
            //    const uint8_t drmHeader[],
            //    uint32_t drmHeaderLength,
            //    ISessionExt*& session) = 0;
            //

            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            uint32_t sessionId = parameters.Number<uint32_t>();

            const uint8_t* contentIdPtr = nullptr;
            uint32_t contentIdLength = parameters.LockBuffer<uint32_t>(contentIdPtr);

            OCDM::ISessionExt::LicenseTypeExt licenseType = parameters.Number<OCDM::ISessionExt::LicenseTypeExt>();

            const uint8_t* drmHeader = nullptr;
            uint32_t drmHeaderLength = parameters.LockBuffer<uint32_t>(drmHeader);

            OCDM::ISessionExt* session = nullptr;
            OCDM::IAccessorOCDMExt* accessor =  message->Parameters().Implementation<OCDM::IAccessorOCDMExt>();

            const char * contentId = reinterpret_cast<const char *>(contentIdPtr);
            OCDM::OCDM_RESULT result = accessor->CreateSessionExt(sessionId, contentId, contentIdLength, licenseType, drmHeader, drmHeaderLength, session);

            response.Number<OCDM::OCDM_RESULT>(result);


            response.Number<OCDM::ISessionExt*>(session);
        },
    };

    //
    // OCDM::IAccessorOCDM::INotification interface stub definitions (interface/ICDM.h)
    //
    ProxyStub::MethodHandler AccesorOCDMNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Create (
            //     const std::string& sessionId) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());

            std::string sessionId = parameters.Text();

            message->Parameters().Implementation<OCDM::IAccessorOCDM::INotification>()->Create(sessionId);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Destroy (
            //     const std::string& sessionId) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());

            std::string sessionId = parameters.Text();

            message->Parameters().Implementation<OCDM::IAccessorOCDM::INotification>()->Destroy(sessionId);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // static void KeyChange(
            //     const string& sessionId, const uint8 keyId[], const uint8_t length) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());

            const uint8_t* keyData;
            std::string sessionId = parameters.Text();
            uint8_t keyDataLength = parameters.LockBuffer<uint8_t>(keyData);
            parameters.UnlockBuffer(keyDataLength);
            OCDM::ISession::KeyStatus status = parameters.Number<OCDM::ISession::KeyStatus>();

            message->Parameters().Implementation<OCDM::IAccessorOCDM::INotification>()->KeyChange(sessionId, keyData, keyDataLength, status);


        },
        nullptr
    };

    //
    // OCDM::ISession::ICallback interface stub definitions (interface/ICDM.h)
    //
    ProxyStub::MethodHandler CallbackStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Event fired when a key message is successfully created.
            // virtual void OnKeyMessage(
            //    const uint8_t* keyMessage, //__in_bcount(f_cbKeyMessage)
            //    const uint16_t keyLength, //__in
            //    const string URL) = 0; //__in_z_opt
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const uint8_t* buffer;
            uint16_t length = parameters.LockBuffer<uint16_t>(buffer);
            parameters.UnlockBuffer(length);
            string URL = parameters.Text();

            message->Parameters().Implementation<OCDM::ISession::ICallback>()->OnKeyMessage(buffer, length, URL);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Event fired when MediaKeySession has found a usable key.
            // virtual void OnKeyReady() = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
 
            message->Parameters().Implementation<OCDM::ISession::ICallback>()->OnKeyReady();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Event fired when MediaKeySession encounters an error.
            // virtual void OnKeyError(
            //     const int16 error,
            //     const OCDM_RESULT sysError,
            //     const string errorMessage) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            uint16_t error = parameters.Number<uint16_t>();
            OCDM::OCDM_RESULT sysError = parameters.Number<OCDM::OCDM_RESULT>();
            string data = parameters.Text();
 
            message->Parameters().Implementation<OCDM::ISession::ICallback>()->OnKeyError(error, sysError, data);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void OnKeyStatusUpdate(const string keyMessage) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            OCDM::ISession::KeyStatus status = parameters.Number<OCDM::ISession::KeyStatus>();
 
            message->Parameters().Implementation<OCDM::ISession::ICallback>()->OnKeyStatusUpdate(status);
        },
        nullptr
    };

    //
    // OCDM::ISession interface stub definitions (interface/ICDM.h)
    //
    ProxyStub::MethodHandler SessionStubMethods[] = {

       [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Loads the data stored for the specified session into the cdm object
            // virtual OCDM_RESULT Load() = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());
 
            response.Number(message->Parameters().Implementation<OCDM::ISession>()->Load());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Process a key message response.
            // virtual void Update(
            //    const uint8_t* keyMessage, //__in_bcount(f_cbKeyMessageResponse)
            //    const uint16_t keyLength) = 0; //__in
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const uint8_t* buffer;
            uint16_t length = parameters.LockBuffer<uint16_t>(buffer);
 
            message->Parameters().Implementation<OCDM::ISession>()->Update(buffer, length);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Removes all license(s) and key(s) associated with the session
            // virtual OCDM_RESULT Remove() = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());
 
            response.Number(message->Parameters().Implementation<OCDM::ISession>()->Remove());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Returns the current Key Status in this Session.
            // virtual ISession::KeyStatus Status() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());
 
            response.Number(message->Parameters().Implementation<OCDM::ISession>()->Status());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // 
            // virtual std::string BufferId() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());
 
            response.Text(message->Parameters().Implementation<OCDM::ISession>()->BufferId());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // 
            // virtual void Close() = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
 
            message->Parameters().Implementation<OCDM::ISession>()->Close();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // 
            // virtual void Revoke (OCDM::ISession::ICallback* callback) = 0;
            //
            RPC::Data::Frame::Reader reader(message->Parameters().Reader());

            // Need to find the proxy that goes with the given implementation..
            OCDM::ISession::ICallback* stub = reader.Number<OCDM::ISession::ICallback*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            OCDM::ISession::ICallback* proxy = RPC::Administrator::Instance().FindProxy<OCDM::ISession::ICallback>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Coud not find stub for OCDM::ISession::ICallback: %p"), stub);
            } else {
                message->Parameters().Implementation<OCDM::ISession>()->Revoke(proxy);
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // 
            // virtual std::string BufferId() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());
 
            response.Text(message->Parameters().Implementation<OCDM::ISession>()->SessionId());
        },
 
        nullptr
    };

    ProxyStub::MethodHandler SessionExtStubMethods[] = {
       [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Loads the data stored for the specified session into the cdm object
            // virtual uint32_t SessionIdExt() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->SessionIdExt());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            //
            // virtual std::string BufferIdExt() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Text(message->Parameters().Implementation<OCDM::ISessionExt>()->BufferIdExt());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint16_t PlaylevelCompressedVideo() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->PlaylevelCompressedVideo());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint16_t PlaylevelUncompressedVideo() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->PlaylevelUncompressedVideo());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint16_t PlaylevelAnalogVideo() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->PlaylevelAnalogVideo());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint16_t PlaylevelCompressedAudio() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->PlaylevelCompressedAudio());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint16_t PlaylevelUncompressedAudio() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->PlaylevelUncompressedAudio());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual std::string GetContentIdExt() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Text(message->Parameters().Implementation<OCDM::ISessionExt>()->GetContentIdExt());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void SetContentIdExt(const std::string & contentId) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            std::string contentId = parameters.Text();
            message->Parameters().Implementation<OCDM::ISessionExt>()->SetContentIdExt(contentId);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual LicenseTypeExt GetLicenseTypeExt() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->GetLicenseTypeExt());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void SetLicenseTypeExt(LicenseTypeExt licenseType) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            OCDM::ISessionExt::LicenseTypeExt licenseType = parameters.Number<OCDM::ISessionExt::LicenseTypeExt>();
            message->Parameters().Implementation<OCDM::ISessionExt>()->SetLicenseTypeExt(licenseType);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual SessionStateExt GetSessionStateExt() const = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            response.Number(message->Parameters().Implementation<OCDM::ISessionExt>()->GetSessionStateExt());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void SetSessionStateExt(SessionStateExt sessionState) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            OCDM::ISessionExt::SessionStateExt sessionState = parameters.Number<OCDM::ISessionExt::SessionStateExt>();
            message->Parameters().Implementation<OCDM::ISessionExt>()->SetSessionStateExt(sessionState);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual OCDM_RESULT SetDrmHeader(const char drmHeader[], uint32_t drmHeaderLength) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            const uint8_t* drmHeader = nullptr;
            uint32_t length = parameters.LockBuffer<uint32_t>(drmHeader);

            OCDM::OCDM_RESULT result = message->Parameters().Implementation<OCDM::ISessionExt>()->SetDrmHeader(drmHeader, length);

            response.Number(result);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual OCDM_RESULT GetChallengeDataNetflix(uint8_t * challenge, uint32_t * challengeSize, uint32_t isLDL) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            const uint8_t* buffer = nullptr;
            uint32_t challengeSize = parameters.LockBuffer<uint32_t>(buffer);
            uint32_t isLDL = parameters.Number<uint32_t>();

            uint32_t orgChallengeSize = challengeSize;
            uint8_t* challenge = const_cast<uint8_t*>(buffer);

            OCDM::OCDM_RESULT result = message->Parameters().Implementation<OCDM::ISessionExt>()->GetChallengeDataNetflix(challenge, challengeSize, isLDL);

            // TODO: do we need this if/else
            // TODO: use return code ("result") instead?
            if (orgChallengeSize == 0) {
                // First run, just getting the buffer size.
                response.Buffer(0, nullptr);
            } else {
                // Second run, interested in actual buffer.
                response.Buffer(challengeSize, challenge);
            }

            response.Number(challengeSize);
            response.Number(result);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual OCDM_RESULT StoreLicenseData(const uint8_t licenseData[], uint32_t licenseDataSize, unsigned char * secureStopId) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            const uint8_t* licenseData = nullptr;
            uint32_t licenseDataSize = 0;
            const uint8_t* secureStopIdBuffer = nullptr;
            uint32_t secureStopIdSize = parameters.LockBuffer<uint32_t>(secureStopIdBuffer);
            licenseDataSize = parameters.LockBuffer<uint32_t>(licenseData);

            uint8_t* secureStopId = const_cast<uint8_t*>(secureStopIdBuffer);
            ASSERT(secureStopIdSize == 16);

            OCDM::OCDM_RESULT result = message->Parameters().Implementation<OCDM::ISessionExt>()->StoreLicenseData(licenseData, licenseDataSize, secureStopId);

            response.Buffer(secureStopIdSize, secureStopId);
            response.Number(result);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual OCDM_RESULT InitDecryptContextByKid() = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            OCDM::OCDM_RESULT result = message->Parameters().Implementation<OCDM::ISessionExt>()->InitDecryptContextByKid();

            response.Number(result);
        },
    };

    typedef ProxyStub::StubType<OCDM::IAccessorOCDM, AccesorOCDMStubMethods, ProxyStub::UnknownStub> AccessorOCDMStub;
    typedef ProxyStub::StubType<OCDM::IAccessorOCDMExt, AccesorOCDMExtStubMethods, ProxyStub::UnknownStub> AccessorOCDMExtStub;
    typedef ProxyStub::StubType<OCDM::IAccessorOCDM::INotification, AccesorOCDMNotificationStubMethods, ProxyStub::UnknownStub> AccessorOCDMNotificationStub;
    typedef ProxyStub::StubType<OCDM::ISession::ICallback, CallbackStubMethods, ProxyStub::UnknownStub> CallbackStub;
    typedef ProxyStub::StubType<OCDM::ISession, SessionStubMethods, ProxyStub::UnknownStub> SessionStub;
    typedef ProxyStub::StubType<OCDM::ISessionExt, SessionExtStubMethods, ProxyStub::UnknownStub> SessionExtStub;

    // -------------------------------------------------------------------------------------------
    // PROXY
    // -------------------------------------------------------------------------------------------
    class AccessorOCDMProxy : public ProxyStub::UnknownProxyType<OCDM::IAccessorOCDM> {
    public:
        AccessorOCDMProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~AccessorOCDMProxy()
        {
        }

    public:
        virtual OCDM::OCDM_RESULT IsTypeSupported(
            const std::string keySystem,
            const std::string mimeType) const override {

            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(keySystem);
            writer.Text(mimeType);
 
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<OCDM::OCDM_RESULT>());
        } 
        virtual OCDM::ISession* Session (
            const std::string sessionId) {

            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(sessionId);
 
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (CreateProxy<OCDM::ISession>(reader.Number<OCDM::ISession*>()));
        }
        virtual OCDM::ISession* Session (
            const uint8_t keyId[],
            const uint8_t keyIdLength) {

            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Buffer(keyIdLength, keyId);
 
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (CreateProxy<OCDM::ISession>(reader.Number<OCDM::ISession*>()));
        }
 
        //
        // Create a MediaKeySession using the supplied init data and CDM data.
        virtual OCDM::OCDM_RESULT CreateSession(
            const string keySystem,
            const int32_t licenseType,
            const string initDataType,
            const uint8_t* initData,
            const uint16_t initDataLength,
            const uint8_t* CDMData,
            const uint16_t CDMDataLength,
            OCDM::ISession::ICallback* callback,
            std::string& sessionId,
            OCDM::ISession*& session) override {

            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(keySystem);
            writer.Number(licenseType);
            writer.Text(initDataType);
            writer.Buffer(initDataLength, initData);
            writer.Buffer(CDMDataLength, CDMData);
            writer.Number(callback);

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            OCDM::OCDM_RESULT result = reader.Number<OCDM::OCDM_RESULT>();

            sessionId = reader.Text(); 
            session = CreateProxy<OCDM::ISession>(reader.Number<OCDM::ISession*>());

            return (result);
        }
        //
        // Set Server Certificate
        virtual OCDM::OCDM_RESULT SetServerCertificate(
            const string keySystem,
            const uint8_t* serverCertificate,
            const uint16_t serverCertificateLength) override {

            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(keySystem);
            writer.Buffer(serverCertificateLength, serverCertificate);

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<OCDM::OCDM_RESULT>());
        }
        //
        // Register for a KeyId change notification
        //
        virtual void Register (OCDM::IAccessorOCDM::INotification* callback) {

            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(callback);

            Invoke(newMessage);
        }
        //
        // Unregister for a KeyId change notification
        //
        virtual void Unregister (OCDM::IAccessorOCDM::INotification* callback) {

            IPCMessage newMessage(BaseClass::Message(6));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(callback);

            Invoke(newMessage);
        }
    };

    class AccessorOCDMExtProxy : public ProxyStub::UnknownProxyType<OCDM::IAccessorOCDMExt> {
    public:
        AccessorOCDMExtProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~AccessorOCDMExtProxy()
        {
        }

    public:
        virtual time_t GetDrmSystemTime() const override {
            IPCMessage newMessage(BaseClass::Message(0));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<time_t>());
        }

        virtual OCDM::OCDM_RESULT CreateSessionExt(
            uint32_t sessionId,
            const char contentId[],
            uint32_t contentIdLength,
            OCDM::ISessionExt::LicenseTypeExt licenseType,
            const uint8_t drmHeader[],
            uint32_t drmHeaderLength,
            OCDM::ISessionExt*& session) override
        {
            const uint8_t * contentIdPtr = reinterpret_cast<const uint8_t *>(contentId);

            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());

            writer.Number(sessionId);
            writer.Buffer(contentIdLength, contentIdPtr);
            writer.Number(licenseType);
            writer.Buffer(drmHeaderLength, drmHeader);

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            OCDM::OCDM_RESULT result = reader.Number<OCDM::OCDM_RESULT>();


            OCDM::ISessionExt* otherSidePtr = reader.Number<OCDM::ISessionExt*>();

            session = CreateProxy<OCDM::ISessionExt>(otherSidePtr);


            return result;
        }
    };
 
    class AccessorOCDMNotificationProxy : public ProxyStub::UnknownProxyType<OCDM::IAccessorOCDM::INotification> {
    public:
        AccessorOCDMNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~AccessorOCDMNotificationProxy()
        {
        }

    public:
        virtual void Create(const string& sessionId) override {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(sessionId);
            Invoke(newMessage);
        }
        virtual void Destroy(const string& sessionId) override {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(sessionId);
            Invoke(newMessage);
        }
        virtual void KeyChange(const string& sessionId, const uint8_t keyId[], const uint8_t length, const OCDM::ISession::KeyStatus status) override {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(sessionId);
            writer.Buffer(length, keyId);
            writer.Number(status);
            Invoke(newMessage);
        }
    };

    class CallbackProxy : public ProxyStub::UnknownProxyType<OCDM::ISession::ICallback> {
    public:
        CallbackProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~CallbackProxy()
        {
        }

    public:
        //
        // Event fired when a key message is successfully created.
        //
        virtual void OnKeyMessage (const uint8_t* keyMessage, const uint16_t length, const string URL)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Buffer(length, keyMessage);
            writer.Text(URL);
            Invoke(newMessage);
        }

        //
        // Event fired when MediaKeySession has found a usable key.
        //
        virtual void OnKeyReady()
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);
        }

        //
        // Event fired when MediaKeySession encounters an error.
        //
        virtual void OnKeyError(const int16_t error, const OCDM::OCDM_RESULT sysError, const string message)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(error);
            writer.Number(sysError);
            writer.Text(message);
            Invoke(newMessage);
        }

        virtual void OnKeyStatusUpdate(const OCDM::ISession::KeyStatus status)
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(status);
            Invoke(newMessage);
        }
    };


    class SessionProxy : public ProxyStub::UnknownProxyType<OCDM::ISession> {
    public:
        SessionProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~SessionProxy()
        {
        }

    public:
        //
        // Loads the data stored for the specified session into the cdm object
        //
        virtual OCDM::OCDM_RESULT Load() override {
            IPCMessage newMessage(BaseClass::Message(0));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<OCDM::OCDM_RESULT>());
        }
        //
        // Process a key message response.
        //
        virtual void Update(const uint8_t* keyMessage, const uint16_t keyLength) override {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Buffer(keyLength, keyMessage);

            Invoke(newMessage);
        } 
        //
        // Removes all license(s) and key(s) associated with the session
        //
        virtual OCDM::OCDM_RESULT Remove() override {
            IPCMessage newMessage(BaseClass::Message(2));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<OCDM::OCDM_RESULT>());
        }
        //
        // report the current status of the Session with respect to the KeyExchange.
        //
        virtual OCDM::ISession::KeyStatus Status() const {

            IPCMessage newMessage(BaseClass::Message(3));
 
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<OCDM::ISession::KeyStatus>());
        }
        //
        // Report the name to be used for the Shared Memory for exchanging the Encrypted fragements.
        //
        virtual std::string BufferId() const {

            IPCMessage newMessage(BaseClass::Message(4));
 
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Text());
        }
        //
        // We are done with the Sesison, close it.
        //
        virtual void Close () {

            IPCMessage newMessage(BaseClass::Message(5));
 
            Invoke(newMessage);
        }
        //
        // Revoke the Session Callback for change notifications
        //
        virtual void Revoke (OCDM::ISession::ICallback* callback) {

            IPCMessage newMessage(BaseClass::Message(6));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(callback);

            Invoke(newMessage);
        }
        //
        // Revoke the Session Callback for change notifications
        //
        virtual std::string SessionId () const {

            IPCMessage newMessage(BaseClass::Message(7));
 
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Text());
        }
 
    };

    class SessionExtProxy : public ProxyStub::UnknownProxyType<OCDM::ISessionExt> {
    public:
        SessionExtProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~SessionExtProxy()
        {
        }

    public:
        virtual uint32_t SessionIdExt() const override {
            IPCMessage newMessage(BaseClass::Message(0));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<uint32_t>());
        }

        virtual std::string BufferIdExt() const override {

            IPCMessage newMessage(BaseClass::Message(1));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Text());
        }

        virtual uint16_t PlaylevelCompressedVideo() const override {

            IPCMessage newMessage(BaseClass::Message(2));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<uint16_t>());
        }

        virtual uint16_t PlaylevelUncompressedVideo() const override {

            IPCMessage newMessage(BaseClass::Message(3));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<uint16_t>());
        }

        virtual uint16_t PlaylevelAnalogVideo() const override {

            IPCMessage newMessage(BaseClass::Message(4));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<uint16_t>());
        }

        virtual uint16_t PlaylevelCompressedAudio() const override {

            IPCMessage newMessage(BaseClass::Message(5));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<uint16_t>());
        }

        virtual uint16_t PlaylevelUncompressedAudio() const override {

            IPCMessage newMessage(BaseClass::Message(6));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Number<uint16_t>());
        }

        virtual std::string GetContentIdExt() const override {

            IPCMessage newMessage(BaseClass::Message(7));

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (reader.Text());
        }

        virtual void SetContentIdExt(const std::string & contentId) override {

            IPCMessage newMessage(BaseClass::Message(8));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(contentId);

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
        }

        virtual LicenseTypeExt GetLicenseTypeExt() const override {
            IPCMessage newMessage(BaseClass::Message(9));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Number<LicenseTypeExt>();
        }

        virtual void SetLicenseTypeExt(LicenseTypeExt licenseType) override {
            IPCMessage newMessage(BaseClass::Message(10));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(licenseType);

            Invoke(newMessage);
        }

        virtual SessionStateExt GetSessionStateExt() const override {
            IPCMessage newMessage(BaseClass::Message(11));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Number<SessionStateExt>();
        }

        virtual void SetSessionStateExt(SessionStateExt sessionState) override {
            IPCMessage newMessage(BaseClass::Message(12));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(sessionState);

            Invoke(newMessage);
        }

        virtual OCDM::OCDM_RESULT SetDrmHeader(const uint8_t drmHeader[], uint32_t drmHeaderLength) override {
            IPCMessage newMessage(BaseClass::Message(13));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());

            writer.Buffer(drmHeaderLength, drmHeader);

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            OCDM::OCDM_RESULT result = reader.Number<OCDM::OCDM_RESULT >();
            return result;
        }

        virtual OCDM::OCDM_RESULT GetChallengeDataNetflix(uint8_t * challenge, uint32_t & challengeSize, uint32_t isLDL) override {
            IPCMessage newMessage(BaseClass::Message(14));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());

            writer.Buffer(challengeSize, challenge);
            writer.Number(isLDL);

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            reader.Buffer(challengeSize, challenge);
            challengeSize = reader.Number<uint32_t>();

            OCDM::OCDM_RESULT result = reader.Number<OCDM::OCDM_RESULT >();
            return result;
        }

        virtual OCDM::OCDM_RESULT StoreLicenseData(const uint8_t licenseData[], uint32_t licenseDataSize, unsigned char * secureStopId) override {
            IPCMessage newMessage(BaseClass::Message(15));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());

            //writer.Buffer(licenseDataSize, licenseData);
            const uint32_t secureStopIdSize = 16;
            writer.Buffer(secureStopIdSize, secureStopId);
            writer.Buffer(licenseDataSize, licenseData);

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            reader.Buffer(16, secureStopId);

            OCDM::OCDM_RESULT result = reader.Number<OCDM::OCDM_RESULT >();
            return result;
        }

        virtual OCDM::OCDM_RESULT InitDecryptContextByKid() override {
            IPCMessage newMessage(BaseClass::Message(16));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());

            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            OCDM::OCDM_RESULT result = reader.Number<OCDM::OCDM_RESULT >();

            return result;
        }
    };
 
    // -------------------------------------------------------------------------------------------
    // These proxy stubs are "loaded" by the next method, which needs to be explicitely called
    // since the interface is a dedicated interface and needs loading, if required by a 
    // wrapper aroundthe interface. 
    // -------------------------------------------------------------------------------------------
namespace {
    class Instantiation {
    public:
        Instantiation()
        {
            RPC::Administrator::Instance().Announce<OCDM::ISession::ICallback, CallbackProxy, CallbackStub>();
            RPC::Administrator::Instance().Announce<OCDM::ISession, SessionProxy, SessionStub>();
            RPC::Administrator::Instance().Announce<OCDM::ISessionExt, SessionExtProxy, SessionExtStub>();
            RPC::Administrator::Instance().Announce<OCDM::IAccessorOCDM, AccessorOCDMProxy, AccessorOCDMStub>();
            RPC::Administrator::Instance().Announce<OCDM::IAccessorOCDMExt, AccessorOCDMExtProxy, AccessorOCDMExtStub>();
            RPC::Administrator::Instance().Announce<OCDM::IAccessorOCDM::INotification, AccessorOCDMNotificationProxy, AccessorOCDMNotificationStub>();
        }

        ~Instantiation()
        {
        }

    } OCDMProxyStubRegistration;
}


} // namespace WPEFramework

extern "C" {
	void* opencdm_announce_proxy_stubs() {
		return (&WPEFramework::OCDMProxyStubRegistration);
	}
}
