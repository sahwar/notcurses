#include "main.h"
#include "egcpool.h"

TEST_CASE("Bidi") {
  auto nc_ = testing_notcurses();
  if(!nc_){
    return;
  }
  if(!notcurses_canutf8(nc_)){
    CHECK(0 == notcurses_stop(nc_));
    return;
  }
  struct ncplane* n_ = notcurses_stdplane(nc_);
  REQUIRE(nullptr != n_);

  SUBCASE("Hebrew") {
    ncplane_set_scrolling(n_, true);
    CHECK(0 < ncplane_putstr(n_, "ט כשתקע המלאך החמישי בשופרו ראיתי כוכב נופל ארצה מן מהשמים, וניתן לו מפתח התהום"));
    uint16_t stylemask;
    uint64_t channels;
    auto egc = ncplane_at_yx(n_, 0, 0, &stylemask, &channels);
    CHECK(0 == strcmp(egc, "ט"));
    // FIXME yes, we place this at 0,0 in our internal view...and yet it
    // is actually placed at the rightmost cell :/
    CHECK(0 == notcurses_render(nc_));
  }

  // common teardown
  CHECK(0 == notcurses_stop(nc_));
}