import com.iflytek.cloud.speech.RecognizerListener;
import com.iflytek.cloud.speech.RecognizerResult;
import com.iflytek.cloud.speech.SpeechConstant;
import com.iflytek.cloud.speech.SpeechError;
import com.iflytek.cloud.speech.SpeechRecognizer;
import com.iflytek.cloud.speech.SpeechUtility;;

public class Main {

	public static void main(String[] args) {
		SpeechUtility.createUtility(SpeechConstant.APPID + "=5853ec06");
		// 1.创建SpeechRecognizer对象
		SpeechRecognizer mIat = SpeechRecognizer.createRecognizer();
		// 2.设置听写参数，详见《iFlytek MSC Reference Manual》SpeechConstant类
		mIat.setParameter(SpeechConstant.DOMAIN, "iat");
		mIat.setParameter(SpeechConstant.LANGUAGE, "zh_cn");
		mIat.setParameter(SpeechConstant.ACCENT, "mandarin ");

		// 听写监听器
		RecognizerListener mRecoListener = new RecognizerListener() {
			// 听写结果回调接口(返回Json格式结果，用户可参见附录)；
			// 一般情况下会通过onResults接口多次返回结果，完整的识别内容是多次结果的累加；
			// 关于解析Json的代码可参见MscDemo中JsonParser类；
			// isLast等于true时会话结束。
			public void onResult(RecognizerResult results, boolean isLast) {
				System.out.println("Result:" + results.getResultString());
			}

			// 会话发生错误回调接口
			public void onError(SpeechError error) {
				error.getErrorDescription(true); // 获取错误码描述
			}

			// 开始录音
			public void onBeginOfSpeech() {
			}

			// 音量值0~30
			public void onVolumeChanged(int volume) {
			}

			// 结束录音
			public void onEndOfSpeech() {
			}

			// 扩展用接口
			public void onEvent(int eventType, int arg1, int arg2, String msg) {
			}
		};

		// 3.开始听写
		mIat.startListening(mRecoListener);
		mRecoListener.onBeginOfSpeech();
		// mRecoListener.onResult(arg0, arg1);
	}

}
