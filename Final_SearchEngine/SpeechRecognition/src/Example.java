import java.util.ArrayList;

import com.iflytek.cloud.speech.RecognizerListener;
import com.iflytek.cloud.speech.RecognizerResult;
import com.iflytek.cloud.speech.SpeechConstant;
import com.iflytek.cloud.speech.SpeechError;
import com.iflytek.cloud.speech.SpeechRecognizer;
import com.iflytek.cloud.speech.SpeechUtility;

public class Example {
	/***
	 * 这里需要改成你自己的实际appid
	 */
	private String version = "5853ec06";
	private SpeechRecognizer recognizer;
	private StringBuffer rStr = new StringBuffer();
	/***
	 * 初始化声音组件
	 */
	{
		if (SpeechRecognizer.getRecognizer() == null)
			SpeechRecognizer.createRecognizer();
		recognizer = SpeechRecognizer.getRecognizer();
	}

	public String listen() {
		if (rStr.length() != 0)
			rStr.setLength(0);
		// 开始监听语音输入，sms表示文本,vad_eos表示用户停止说话后多长时间表示结束
//		recognizer.startListening(resultListener, "sms", "vad_bos =10000,vad_eos=2000", null);
//		while (true) {
//			if (recognizer.isAvaible())
//				break;
//		}
		recognizer.startListening(resultListener);
		while (true) {
			if (recognizer.isAvaible())
				break;
		}
		return rStr.toString();
	}

	private RecognizerListener resultListener = new RecognizerListener() {
		public void onCancel() {
		}

		public void onEnd(SpeechError mLastError) {
		}

		@Override
		public void onBeginOfSpeech() {
		}

		@Override
		public void onEndOfSpeech() {
		}

		/**
		 * 获取识别结果. 获取ArrayList类型的识别结果，并对结果进行累加，显示到Area里
		 */
		public void onResults(ArrayList results, boolean islast) {
			String text = "";
			for (int i = 0; i < results.size(); i++) {
				RecognizerResult result = (RecognizerResult) results.get(i);
				text += result.toString();
			}
			rStr.append(text);
		}

		@Override
		public void onVolumeChanged(int volume) {
			if (volume == 0)
				volume = 1;
			else if (volume >= 6)
				volume = 6;
		}

		@Override
		public void onError(SpeechError arg0) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onEvent(int arg0, int arg1, int arg2, String arg3) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onResult(RecognizerResult arg0, boolean arg1) {
			// TODO Auto-generated method stub
			
		}
	};

	public static void main(String[] args) {
		SpeechUtility.createUtility(SpeechConstant.APPID + "=5853ec06");
		Example t = new Example();
		System.out.println("我刚才说的:" + t.listen());
		System.out.println("第二句---------------");
		System.out.println("我刚才说的:" + t.listen());
	}
}