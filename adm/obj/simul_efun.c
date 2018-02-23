/* simul_efun.c
 *
 * Tacitus @ LPUniversity
 * 02-APR-05
 * Simul-efun object
 *
 * NOTE: Order does matter!
 *
 */

#pragma show_error_context

/* read_file(string file, int start_line, int number_of_lines);
 *
 * Cratylus @ Dead Souls
 *
 * For some reason, FluffOS read_file() will read
 * a zero-length file as a 65535 length T_INVALID variable.
 * This tends to screw things up for mudlibs using it.
 *
 */
varargs string read_file(string file, int start_line, int number_of_lines)
{
    if (file_size(file) == 0) return "";
    return efun::read_file(file, start_line, number_of_lines);
}

#include "/adm/simul_efun/security.c"
#include "/adm/simul_efun/overrides.c"
#include "/adm/simul_efun/system.c"
#include "/adm/simul_efun/exists.c"
#include "/adm/simul_efun/user.c"
#include "/adm/simul_efun/resolve_path.c"
#include "/adm/simul_efun/file.c"
#include "/adm/simul_efun/object.c"
#include "/adm/simul_efun/socket.c"
#include "/adm/simul_efun/strings.c"
#include "/adm/simul_efun/messages.c"
#include "/adm/simul_efun/math.c"
