#ifndef TICK_TO_KLINE_H_
#define TICK_TO_KLINE_H_

#include <stdint.h>
#include <vector>

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))


typedef struct TickField {
	uint64_t		TimeStamp;				///时间戳，毫秒
	double			LastPrice;
	uint64_t		OpenInterest;
	uint64_t		Volume;
	double			AskPrice;
	uint64_t		AskVolume;
	double			BidPrice;
	uint64_t		BidVolume;
} TickField;


typedef struct KlineField {
	uint64_t		TimeStamp;				///时间戳，毫秒
	double			Open;
	double			High;
	double			Low;
	double			Close;
	double			Average;
	int				UpOrDown;
	uint64_t		InterOpenInterest;		///周期起始的持仓量
	uint64_t		InterVolume;			///周期起始的成交量
	uint64_t		DeltaOpenInterest;
	uint64_t		DeltaVolume;
	double			DeltaCO;
} KlineField;


class KlineContainer 
{
private:
	bool flag = false;
	TickField lastTick;
	TickField currTick;

	//std::vector<KlineField> *Kline = nullptr;
	std::vector<KlineField> *kline3s = nullptr;
	std::vector<KlineField> *kline5s = nullptr;
	std::vector<KlineField> *kline10s = nullptr;
	std::vector<KlineField> *kline15s = nullptr;

	void InsertTick(std::vector<KlineField> *, TickField &, int);

public:
	KlineContainer();
	void InsertTick(TickField &);
};

#endif // !TICK_TO_KLINE_H_

