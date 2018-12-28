#include "tick2kline.h"


KlineContainer::KlineContainer()
{
	//Kline = new std::vector<KlineField>(65535);
	kline3s = new std::vector<KlineField>(65535);
	kline5s = new std::vector<KlineField>(65535); 
	kline10s = new std::vector<KlineField>(65535);
	kline15s = new std::vector<KlineField>(65535);
}


void KlineContainer::InsertTick(TickField &tick)
{
	TickField t;
	memcpy_s(&t, sizeof(TickField), &tick, sizeof(TickField));
	memcpy_s(&lastTick, sizeof(TickField), &currTick, sizeof(TickField));
	memcpy_s(&currTick, sizeof(TickField), &tick, sizeof(TickField));
	if (!flag) {
		flag = true;
		return;
	}

	t.Volume = currTick.Volume - lastTick.Volume;
	t.OpenInterest = currTick.OpenInterest - lastTick.OpenInterest;

	InsertTick(kline3s, t, 3);
	InsertTick(kline5s, t, 5);
	InsertTick(kline10s, t, 10);
	InsertTick(kline15s, t, 15);
}


void KlineContainer::InsertTick(std::vector<KlineField> *kline, TickField &tick, int gap)
{
	uint64_t timestamp = (tick.TimeStamp / (1000 * gap)) * (1000 * gap);

	if (!kline->empty()) {	///not empty
		std::vector<KlineField>::iterator pt = kline->end() - 1;
		if (timestamp == (*pt).TimeStamp) {
			(*pt).High = max((*pt).High, tick.LastPrice);
			(*pt).Low = max((*pt).Low, tick.LastPrice);
			(*pt).Close = tick.LastPrice;
			(*pt).Average = ((*pt).High + (*pt).Low + (*pt).Close) / 3;
			(*pt).UpOrDown = (*pt).Open > (*pt).Close ? -1 : ((*pt).Open == (*pt).Close ? 0 : 1);
			(*pt).DeltaOpenInterest = tick.OpenInterest - (*pt).InterOpenInterest;
			(*pt).DeltaVolume = tick.Volume - (*pt).InterVolume;
			(*pt).DeltaCO = (*pt).Close - (*pt).Open;
			return;
		}
	}

	KlineField k = { 0 };
	k.TimeStamp = timestamp;
	k.Open = tick.LastPrice;
	k.High = tick.LastPrice;
	k.Low = tick.LastPrice;
	k.Close = tick.LastPrice;
	k.Average = tick.LastPrice;
	k.UpOrDown = 0;
	k.InterOpenInterest = tick.OpenInterest;
	k.InterVolume = tick.Volume;
	k.DeltaOpenInterest = tick.OpenInterest;
	k.DeltaVolume = tick.Volume;
	k.DeltaCO = 0;
	kline->push_back(k);
}

