#ifndef __CHKS_FIELD_H__
#define __CHKS_FIELD_H__

#include <gtk/gtk.h>

#define CHKS_CLASS_FIELD "chks-field"

#define CHKS_CLASS_ONE "chks-player-one"
#define CHKS_CLASS_TWO "chks-player-two"

#define CHKS_CLASS_ONE_PRE "chks-player-one-pre"
#define CHKS_CLASS_TWO_PRE "chks-player-two-pre"

typedef enum {
	CHKS_OWNER_NONE,
	CHKS_OWNER_ONE,
	CHKS_OWNER_TWO,
} ChksOwner;

class ChksView;

class ChksField {
private:
	/* Widget */
	GtkWidget *button;

	/* Connection to view */
	ChksView *view;

	/* States */
	ChksOwner owner;
	gboolean is_queen;
	gint col;
	gint row;

public:
	GtkWidget *get_button();
	ChksView *get_view();
	void set_view(ChksView *);
	ChksOwner get_owner();
	void set_owner(ChksOwner);
	ChksOwner get_initial_owner();
	gboolean get_is_queen();
	void set_preowner(ChksOwner);
	void set_is_queen(gboolean);
	gint get_col();
	gint get_row();
	ChksField(gint, gint);
};

#endif /* __CHKS_FIELD_H__ */