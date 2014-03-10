package org.stagex.danmaku.player;

import android.util.Log;
import android.view.SurfaceHolder;

public abstract class AbsMediaPlayer {

	private static final String LOGTAG = "DANMAKU-AbsMediaPlayer";

	public interface OnBufferingUpdateListener {
		public void onBufferingUpdate(AbsMediaPlayer mp, int percent);
	}

	public interface OnCompletionListener {
		public void onCompletion(AbsMediaPlayer mp);
	}

	public interface OnErrorListener {
		public boolean onError(AbsMediaPlayer mp, int what, int extra);
	}

	public interface OnInfoListener {
		public boolean onInfo(AbsMediaPlayer mp, int what, int extra);
	}

	public interface OnPreparedListener {
		public void onPrepaired(AbsMediaPlayer mp);
	}

	public interface OnProgressUpdateListener {
		public void onProgressUpdate(AbsMediaPlayer mp, int time, int length);
	}

	public abstract int getCurrentPosition();

	public abstract int getDuration();

	public abstract int getVideoHeight();

	public abstract int getVideoWidth();

	public abstract boolean isLooping();

	public abstract boolean isPlaying();

	public abstract void pause();

	public abstract void prepare();

	public abstract void prepareAsync();

	public abstract void release();

	public abstract void reset();

	public abstract void seekTo(int msec);

	public abstract void setDataSource(String path);

	public abstract void setDisplay(SurfaceHolder holder);

	public abstract void setLooping(boolean looping);

	public abstract void setOnBufferingUpdateListener(
			AbsMediaPlayer.OnBufferingUpdateListener listener);

	public abstract void setOnCompletionListener(
			AbsMediaPlayer.OnCompletionListener listener);

	public abstract void setOnErrorListener(
			AbsMediaPlayer.OnErrorListener listener);

	public abstract void setOnInfoListener(
			AbsMediaPlayer.OnInfoListener listener);

	public abstract void setOnPreparedListener(
			AbsMediaPlayer.OnPreparedListener listener);

	public abstract void setOnProgressUpdateListener(
			AbsMediaPlayer.OnProgressUpdateListener listener);

	public abstract void start();

	public abstract void stop();

	/* */

	public abstract int getAudioTrackCount();

	public abstract int getAudioTrack();

	public abstract void setAudioTrack(int index);

	public abstract int getSubtitleTrackCount();

	public abstract int getSubtitleTrack();

	public abstract void setSubtitleTrack(int index);

	protected static AbsMediaPlayer sDefMediaPlayer = null;
	protected static AbsMediaPlayer sVlcMediaPlayer = null;

	protected static AbsMediaPlayer getDefMediaPlayer() {
		if (sDefMediaPlayer == null)
			sDefMediaPlayer = new DefMediaPlayer();
		Log.d(LOGTAG, "using DefMediaPlayer");
		return sDefMediaPlayer;
	}

	protected static AbsMediaPlayer getVlcMediaPlayer() {
		if (sVlcMediaPlayer == null)
			sVlcMediaPlayer = new VlcMediaPlayer();
		Log.d(LOGTAG, "using VlcMediaPlayer");
		return sVlcMediaPlayer;
	}

	public static AbsMediaPlayer getMediaPlayer(boolean useDefault) {
		return useDefault ? getDefMediaPlayer() : getVlcMediaPlayer();
	}

}
