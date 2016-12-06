#include "wing.h"

HimeturuWing::HimeturuWing(wingservo l, wingservo r) {
	winglsv = l;
	wingrsv = r;
	ics.begin();
}

void HimeturuWing::wakeup() {
	int fls, flee, flde, frs, free, frde;
	fls = flee = flde = frs = free = frde = 0;

	winglpos.spoiler = ics.position(0, winglsv.spoiler);
	winglpos.elebon_e = ics.position(0, winglsv.elebon_el);
	if (winglsv.elebon_el != winglsv.elebon_er) {
		winglpos.elebon_e = ics.position(0, winglsv.elebon_er);
	}
	winglpos.elebon_d = ics.position(0, winglsv.elebon_dl);
	if (winglsv.elebon_dl != winglsv.elebon_dr) {
		winglpos.elebon_d = ics.position(0, winglsv.elebon_dr);
	}

	wingrpos.spoiler = ics.position(0, wingrsv.spoiler);
	wingrpos.elebon_e = ics.position(0, wingrsv.elebon_el);
	if (winglsv.elebon_el != winglsv.elebon_er) {
		wingrpos.elebon_e = ics.position(0, wingrsv.elebon_er);
	}
	wingrpos.elebon_d = ics.position(0, wingrsv.elebon_dl);
	if (winglsv.elebon_dl != winglsv.elebon_dr) {
		wingrpos.elebon_d = ics.position(0, wingrsv.elebon_dr);
	}

}

void HimeturuWing::setSpoiler(axis ax) {



}

void HimeturuWing::setElebon(axis ax) {

}