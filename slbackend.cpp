#include "slbackend.h"

#include <stdlib.h> // system()

void SLBackend::record()
{
	_overdub = false;
	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record");
	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_off");
}

void SLBackend::stop()
{
	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s pause");
	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
}

void SLBackend::endRecordOrOverdub()
{
	if (_overdub)
		system("oscsend osc.udp://localhost:9951 /sl/-1/hit s overdub");
	else
		system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record");
}

void SLBackend::playback()
{
	endRecordOrOverdub();

	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_off");
}

void SLBackend::overdub()
{
	_overdub = true;
	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s overdub");
	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_off");
}

void SLBackend::deleteLoop()
{
	_overdub = false;
}

void SLBackend::undoredo() {
	if (_undo)
		system("oscsend osc.udp://localhost:9951 /sl/-1/hit s undo");
	else
		system("oscsend osc.udp://localhost:9951 /sl/-1/hit s redo");

	_undo = !_undo;
}

void SLBackend::trigger()
{
	system("oscsend osc.udp://localhost:9951 /sl/-1/hit s trigger");
}
