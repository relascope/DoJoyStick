#ifndef SLBACKEND_H
#define SLBACKEND_H

/**
 * @brief The SLBackend class
 * sends commands to the SooperLooper
 */
class SLBackend {
public:
	SLBackend() {}
public:
	void record();
	void stop();
	void playback();
	void overdub();
	void deleteLoop();
	void undoredo();
	void trigger();

private:
	void endRecordOrOverdub();

private:
	bool _overdub = false;
	bool _undo = true;
};

#endif // SLBACKEND_H
