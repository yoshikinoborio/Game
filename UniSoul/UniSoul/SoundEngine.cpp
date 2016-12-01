/*!
* @brief	サウンドエンジン
*/

#include "stdafx.h"
#include "SoundEngine.h"
#include "WaveFile.h"
#include "SoundSource.h"

#define NUM_PRESETS 30

namespace {
	//マイクロソフトのサンプルから引っ張ってきたサウンドコーン。
	// Specify sound cone to add directionality to listener for artistic effect:
	// Emitters behind the listener are defined here to be more attenuated,
	// have a lower LPF cutoff frequency,
	// yet have a slightly higher reverb send level.
	//エミッターの向きに対して、単一チャンネルの非 LFE エミッターの方向を DSP 動作のスケーリングによって指定します。
	//第一引数。内部コーンの角度(ラジアン単位) です。この値は 0.0f ～ X3DAUDIO_2PI の範囲内でなければなりません。
	//第二外部コーンの角度(ラジアン単位) です。この値は InnerAngle ～ X3DAUDIO_2PI の範囲内でなければなりません。
	//第三内部コーン上/内のボリューム スケーラです。この値は 0.0f ～ 2.0f の範囲内でなければなりません。
	//第四外部コーン上 / 以降のボリューム スケーラです。この値は 0.0f ～ 2.0f の範囲内でなければなりません。
	//第五内部コーン上 / 内の LPF ダイレクト パスまたはリバーブ パスの係数スケーラです。この値は LPF 計算のみに使用され、0.0f ～ 1.0f の範囲内でなければなりません。
	//第六外部コーン上/以降の LPF ダイレクト パスまたはリバーブ パスの係数スケーラです。この値は LPF 計算のみに使用され、0.0f ～ 1.0f の範囲内でなければなりません。
	//第七内部コーン上/内のリバーブ センド レベル スケーラです。この値は 0.0f ～ 2.0f の範囲内でなければなりません。
	//第八外部コーン上/以降のリバーブ センド レベル スケーラです。この値は 0.0f ～ 2.0f の範囲内でなければなりません。
	static const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI*5.0f / 6.0f, X3DAUDIO_PI*11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };
	// Specify LFE level distance curve such that it rolls off much sooner than
	// all non-LFE channels, making use of the subwoofer more dramatic.
	//線形セグメントで構成された明示的な区分曲線を定義し、正規化された距離に対して DSP 動作を直接定義します。
	//第一引数。正規化された距離です。この値は 0.0f ～ 1.0f の範囲内でなければなりません。
	//第二。DSP コントロールの設定です。
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
	//正規化された一定の距離で DSP 設定を定義します。
	//第一引数。X3DAUDIO_DISTANCE_CURVE_POINT 配列です。この配列には複製があってはならず、距離を基準にして昇順でソートされていなければなりません。
	//第二。距離カーブ上のポイントの数です。すべてのカーブには、0.0f と 1.0f の正規化された距離の値をそれぞれ定義する少なくとも 2 つのエンドポイントがあるので、2 つ以上のポイントがあるはずです。
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_LFE_CurvePoints[0], 3 };

	// Specify reverb send level distance curve such that reverb send increases
	// slightly with distance before rolling off to silence.
	// With the direct channels being increasingly attenuated with distance,
	// this has the effect of increasing the reverb-to-direct sound ratio,
	// reinforcing the perception of distance.
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_Reverb_CurvePoints[0], 3 };

	//第一引数。//元の変更されていないサウンドとなる出力の割合です。許容値は 0 ～ 100 です。
	//第二室内エフェクトの減衰です。許容値は - 10000 ～ 0 で、単位は 1 / 100 デシベルです。
	//第三室内の高周波数エフェクトの減衰です。許容値は -10000 ～ 0 で、単位は 1/100 デシベルです。
	//第四反射される信号のロールオフ係数です。許容値は 0.0 ～ 10.0 です。
	//第五低周波数における残響減衰時間です。許容値は 0.1 ～ 20.0 で、単位は秒です。
	//第六低周波数の減衰時間に対する高周波数の減衰時間の比率です。許容値は 0.1 ～ 2.0 です。
	//第七Room に対する初期反射の減衰です。許容値は -10000 ～ 1000 で、単位は 1/100 デシベルです。
	//第八ダイレクト パスに対する初期反射の遅延時間です。許容値は 0.0 ～ 0.3 で、単位は秒です。
	//第九Room に対する後期残響の減衰です。許容値は -10000 ～ 2000 で、単位は 1/100 デシベルです。
	//第十初期反射の時間に対する、初期反射と後期残響の間の時間制限です。許容値は 0.0 ～ 0.1 で、単位は秒です。
	//第十一後期残響減衰のエコー密度です。許容値は 0 ～ 100 で、単位はパーセントです。
	//第十二後期残響減衰のモード密度です。許容値は 0 ～ 100 で、単位はパーセントです。
	//第十三高周波数を参照します。許容値は 20.0 ～ 20000.0 で、単位は Hz です。
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS PRESET_PARAMS[NUM_PRESETS] =
	{
		XAUDIO2FX_I3DL2_PRESET_FOREST,
		XAUDIO2FX_I3DL2_PRESET_DEFAULT,
		XAUDIO2FX_I3DL2_PRESET_GENERIC,
		XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
		XAUDIO2FX_I3DL2_PRESET_ROOM,
		XAUDIO2FX_I3DL2_PRESET_BATHROOM,
		XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
		XAUDIO2FX_I3DL2_PRESET_STONEROOM,
		XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
		XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
		XAUDIO2FX_I3DL2_PRESET_CAVE,
		XAUDIO2FX_I3DL2_PRESET_ARENA,
		XAUDIO2FX_I3DL2_PRESET_HANGAR,
		XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
		XAUDIO2FX_I3DL2_PRESET_HALLWAY,
		XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
		XAUDIO2FX_I3DL2_PRESET_ALLEY,
		XAUDIO2FX_I3DL2_PRESET_CITY,
		XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
		XAUDIO2FX_I3DL2_PRESET_QUARRY,
		XAUDIO2FX_I3DL2_PRESET_PLAIN,
		XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
		XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
		XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
		XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
		XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
		XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
		XAUDIO2FX_I3DL2_PRESET_PLATE,
	};
}
	/*!
	* @brief	コンストラクタ。
	*/
CSoundEngine::CSoundEngine()
{
	memset(m_hx3DAudio, 0, sizeof(m_hx3DAudio));
}
	/*!
	* @brief	デストラクタ。
	*/
CSoundEngine::~CSoundEngine()
{
	Release();
}
	/*!
	* @brief	初期化。
	*/
void CSoundEngine::Init()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	unsigned int flags = 0;
#ifdef _DEBUG
	flags |= XAUDIO2_DEBUG_ENGINE;
#endif
	//XAUDIO2を初期化。
	HRESULT hr;
	if (FAILED(hr = XAudio2Create(&m_xAudio2, flags)))
	{

		Assert(false);
	}
	//マスターボリュームの作成。
	if (FAILED(hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice)))
	{
		Release();
		Assert(false);
		return;
	}
	//サウンドデバイスの情報を取得。
	XAUDIO2_DEVICE_DETAILS details;
	if (FAILED(hr = m_xAudio2->GetDeviceDetails(0, &details)))
	{
		Release();
		Assert(false);
		return;
	}

	if (details.OutputFormat.Format.nChannels > OUTPUTCHANNELS)
	{
		Release();
		Assert(false);
		return;
	}

	m_channelMask = details.OutputFormat.dwChannelMask;
	m_nChannels = details.OutputFormat.Format.nChannels;

	//リバーブエフェクトを作成。
	flags = 0;
#ifdef _DEBUG
	flags |= XAUDIO2FX_DEBUG;
#endif
	if (FAILED(hr = XAudio2CreateReverb(&m_reverbEffect, flags))) {
		Release();
		Assert(false);
		return;
	}
	//サブミックスボイスを作成。
	XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { m_reverbEffect, TRUE, 1 } };
	XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

	if (FAILED(hr = m_xAudio2->CreateSubmixVoice(&m_submixVoice, 1,
		details.OutputFormat.Format.nSamplesPerSec, 0, 0,
		NULL, &effectChain)))
	{
		Release();
		Assert(false);
		return;
	}
	//デフォルトのFXパラメータを設定。
	XAUDIO2FX_REVERB_PARAMETERS native;
	ReverbConvertI3DL2ToNative(&PRESET_PARAMS[0], &native);
	m_submixVoice->SetEffectParameters(0, &native, sizeof(native));
	//3Dオーディオの初期化。
	const float SPEEDOFSOUND = X3DAUDIO_SPEED_OF_SOUND;
	X3DAudioInitialize(details.OutputFormat.dwChannelMask, SPEEDOFSOUND, m_hx3DAudio);
	m_listener.Position = { 0.0f, 0.0f, 0.0f };
	m_listener.OrientFront = { 0.0f, 0.0f, 1.0f };
	m_listener.OrientTop = { 0.0f, 1.0f, 0.0f };

	/*	m_fListenerAngle = 0.0f;
	m_UseListenerCone = true;
	m_fUseInnerRadius = true;
	m_useRedirectToLFE = ((details.OutputFormat.dwChannelMask & SPEAKER_LOW_FREQUENCY) != 0);*/
	//初期化完了。
	m_isInited = true;
}
	/*!
	* @brief	開放。
	*/
void CSoundEngine::Release()
{
	//波形データバンクを解放。
	m_waveFileBank.ReleaseAll();
	if (m_xAudio2 != nullptr) {
		m_xAudio2->Release();
		m_xAudio2 = nullptr;
	}
	if (m_masteringVoice != nullptr) {
		m_masteringVoice->DestroyVoice();
		m_masteringVoice = nullptr;
	}
	if (m_reverbEffect != nullptr) {
		m_reverbEffect->Release();
		m_reverbEffect = nullptr;
	}
	if (m_submixVoice != nullptr) {
		m_submixVoice->DestroyVoice();
		m_submixVoice = nullptr;
	}
	CoUninitialize();
}
	/*!
	* @brief	XAudio2のソースボイスを作成。
	*/
IXAudio2SourceVoice* CSoundEngine::CreateXAudio2SourceVoice(CWaveFile* waveFile, bool is3DSound)
{
	Assert(waveFile->GetFormat()->nChannels <= INPUTCHANNELS);
	IXAudio2SourceVoice* pSourceVoice;
	if (is3DSound == false) {
		//2Dサウンド。
		if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat())))
		{
			//TK_LOG("Failed CreateSourceVoice");
			return nullptr;
		}
	}
	else {
		//3Dサウンド。
		XAUDIO2_SEND_DESCRIPTOR sendDescriptors[2];
		sendDescriptors[0].Flags = XAUDIO2_SEND_USEFILTER; // LPF direct-path
		sendDescriptors[0].pOutputVoice = CSoundEngine::GetMasteringVoice();
		sendDescriptors[1].Flags = XAUDIO2_SEND_USEFILTER; // LPF reverb-path -- omit for better performance at the cost of less realistic occlusion
		sendDescriptors[1].pOutputVoice = CSoundEngine::GetSubmixVoice();
		const XAUDIO2_VOICE_SENDS sendList = { 2, sendDescriptors };
		if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat(), 0, 2.0f, NULL, &sendList)))
		{
			//TK_LOG("Failed CreateSourceVoice");
			return nullptr;
		}
	}

	return pSourceVoice;
}
	/*!
	* @brief	更新。
	*/
void CSoundEngine::Update()
{
	if (!m_isInited) {
		return;
	}
	//サウンドリスナーの前方向を計算。
	//@todo ここらへんはSoundListenerクラスに後で移動させる。
	//@todo 前方向の計算もこれだと都合が悪い。
	if (m_listener.Position.x != m_listenerPosition.x
		|| m_listener.Position.z != m_listenerPosition.z
		) {
		//リスナーがXZ平面上で動いている。
		D3DXVECTOR3 listenerPos;
		listenerPos = m_listener.Position;
		//動いた分を計算。
		D3DXVECTOR3 vDelta;
		vDelta = m_listenerPosition - listenerPos;
		m_fListenerAngle = float(atan2(m_listener.OrientFront.x, m_listener.OrientFront.z));

		if (m_UseListenerCone == true) {
			m_listener.pCone = (X3DAUDIO_CONE*)&Listener_DirectionalCone;
		}
		else {
			m_listener.pCone = NULL;
		}
	}
	float deltaTime = 1.0f / 60.0f;
	if (deltaTime > 0.0f) {
		//リスナーの移動速度を計算する。
		D3DXVECTOR3 vel;
		vel = m_listener.Position;
		vel = m_listenerPosition - vel;
		vel /= deltaTime;
		m_listener.Position = m_listenerPosition;
		m_listener.Velocity = vel;
	}
	DWORD dwCalcFlags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER
		| X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_LPF_REVERB
		| X3DAUDIO_CALCULATE_REVERB;
	if (m_useRedirectToLFE)
	{
		// On devices with an LFE channel, allow the mono source data
		// to be routed to the LFE destination channel.
		dwCalcFlags |= X3DAUDIO_CALCULATE_REDIRECT_TO_LFE;
	}

	//3Dサウンドの計算。
	for (auto& soundSource : m_3dSoundSource) {
		X3DAUDIO_EMITTER emitter;

		emitter.pCone = &m_emitterCone;
		emitter.pCone->InnerAngle = 0.0f;
		// Setting the inner cone angles to X3DAUDIO_2PI and
		// outer cone other than 0 causes
		// the emitter to act like a point emitter using the
		// INNER cone settings only.
		emitter.pCone->OuterAngle = 0.0f;
		// Setting the outer cone angles to zero causes
		// the emitter to act like a point emitter using the
		// OUTER cone settings only.
		emitter.pCone->InnerVolume = 0.0f;
		emitter.pCone->OuterVolume = 1.0f;
		emitter.pCone->InnerLPF = 0.0f;
		emitter.pCone->OuterLPF = 1.0f;
		emitter.pCone->InnerReverb = 0.0f;
		emitter.pCone->OuterReverb = 1.0f;


		emitter.OrientFront = D3DXVECTOR3(0, 0, 1);
		emitter.OrientTop = D3DXVECTOR3(0, 1, 0);
		emitter.ChannelCount = INPUTCHANNELS;
		emitter.ChannelRadius = 1.0f;
		emitter.pChannelAzimuths = soundSource->GetEmitterAzimuths();

		// Use of Inner radius allows for smoother transitions as
		// a sound travels directly through, above, or below the listener.
		// It also may be used to give elevation cues.
		emitter.InnerRadius = 2.0f;
		emitter.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;;

		emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
		emitter.pLFECurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_LFE_Curve;
		emitter.pLPFDirectCurve = NULL; // use default curve
		emitter.pLPFReverbCurve = NULL; // use default curve
		emitter.pReverbCurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_Reverb_Curve;
		emitter.CurveDistanceScaler = 14.0f;
		emitter.DopplerScaler = 1.0f;

		emitter.Position = soundSource->GetPosition();
		emitter.Velocity = soundSource->GetVelocity();

		if (m_fUseInnerRadius) {
			emitter.InnerRadius = 2.0f;
			emitter.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;
		}
		else {
			emitter.InnerRadius = 0.0f;
			emitter.InnerRadiusAngle = 0.0f;
		}
		X3DAUDIO_DSP_SETTINGS* dspSettings = soundSource->GetDspSettings();
		X3DAudioCalculate(m_hx3DAudio, &m_listener, &emitter, dwCalcFlags,
			dspSettings);
		IXAudio2SourceVoice* voice = soundSource->GetXAudio2SourceVoice();
		if (voice != nullptr)
		{
			// Apply X3DAudio generated DSP settings to XAudio2
			voice->SetFrequencyRatio(dspSettings->DopplerFactor);
			voice->SetOutputMatrix(m_masteringVoice, soundSource->GetNumInputChannel(), m_nChannels,
				soundSource->GetMatrixCoefficients());

			voice->SetOutputMatrix(m_submixVoice, soundSource->GetNumInputChannel(), 1, &dspSettings->ReverbLevel);

			XAUDIO2_FILTER_PARAMETERS FilterParametersDirect = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dspSettings->LPFDirectCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
			voice->SetOutputFilterParameters(m_masteringVoice, &FilterParametersDirect);
			XAUDIO2_FILTER_PARAMETERS FilterParametersReverb = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dspSettings->LPFReverbCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
			voice->SetOutputFilterParameters(m_submixVoice, &FilterParametersReverb);
		}
	}
}