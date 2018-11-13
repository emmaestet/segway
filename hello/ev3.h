#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

//-----------------------------------------------------------------------------

namespace ev3dev {

//-----------------------------------------------------------------------------

typedef std::string         device_type;
typedef std::string         mode_type;
typedef std::set<mode_type> mode_set;
typedef std::string         address_type;

//-----------------------------------------------------------------------------

const address_type INPUT_AUTO;  //!< Automatic input selection
const address_type OUTPUT_AUTO; //!< Automatic output selection

#if defined(EV3DEV_PLATFORM_BRICKPI)
constexpr char INPUT_1[]  = "ttyAMA0:in1";  //!< Sensor port 1
constexpr char INPUT_2[]  = "ttyAMA0:in2";  //!< Sensor port 2
constexpr char INPUT_3[]  = "ttyAMA0:in3";  //!< Sensor port 3
constexpr char INPUT_4[]  = "ttyAMA0:in4";  //!< Sensor port 4

constexpr char OUTPUT_A[] = "ttyAMA0:outA"; //!< Motor port A
constexpr char OUTPUT_B[] = "ttyAMA0:outB"; //!< Motor port B
constexpr char OUTPUT_C[] = "ttyAMA0:outC"; //!< Motor port C
constexpr char OUTPUT_D[] = "ttyAMA0:outD"; //!< Motor port D
#elif defined(EV3DEV_PLATFORM_BRICKPI3)
constexpr char INPUT_1[]  = "spi0.1:S1";  //!< Sensor port 1
constexpr char INPUT_2[]  = "spi0.1:S2";  //!< Sensor port 2
constexpr char INPUT_3[]  = "spi0.1:S3";  //!< Sensor port 3
constexpr char INPUT_4[]  = "spi0.1:S4";  //!< Sensor port 4

constexpr char OUTPUT_A[] = "spi0.1:MA"; //!< Motor port A
constexpr char OUTPUT_B[] = "spi0.1:MB"; //!< Motor port B
constexpr char OUTPUT_C[] = "spi0.1:MC"; //!< Motor port C
constexpr char OUTPUT_D[] = "spi0.1:MD"; //!< Motor port D
#elif defined(EV3DEV_PLATFORM_PISTORMS)
constexpr char INPUT_1[]  = "pistorms:BAS1"; //!< Sensor port 1
constexpr char INPUT_2[]  = "pistorms:BAS2"; //!< Sensor port 2
constexpr char INPUT_3[]  = "pistorms:BBS1"; //!< Sensor port 3
constexpr char INPUT_4[]  = "pistorms:BBS2"; //!< Sensor port 4

constexpr char OUTPUT_A[] = "pistorms:BAM1"; //!< Motor port A
constexpr char OUTPUT_B[] = "pistorms:BAM2"; //!< Motor port B
constexpr char OUTPUT_C[] = "pistorms:BBM1"; //!< Motor port C
constexpr char OUTPUT_D[] = "pistorms:BBM2"; //!< Motor port D
#else // assume EV3DEV_PLATFORM_EV3
constexpr char INPUT_1[]  = "ev3-ports:in1";  //!< Sensor port 1
constexpr char INPUT_2[]  = "ev3-ports:in2";  //!< Sensor port 2
constexpr char INPUT_3[]  = "ev3-ports:in3";  //!< Sensor port 3
constexpr char INPUT_4[]  = "ev3-ports:in4";  //!< Sensor port 4

constexpr char OUTPUT_A[] = "ev3-ports:outA"; //!< Motor port A
constexpr char OUTPUT_B[] = "ev3-ports:outB"; //!< Motor port B
constexpr char OUTPUT_C[] = "ev3-ports:outC"; //!< Motor port C
constexpr char OUTPUT_D[] = "ev3-ports:outD"; //!< Motor port D
#endif

//-----------------------------------------------------------------------------

// Generic device class.
class device
{
public:
  bool connect(const std::string &dir,
               const std::string &pattern,
               const std::map<std::string, std::set<std::string>> &match) noexcept;

  inline bool connected() const { return !_path.empty(); }

  int         device_index() const;

  int         get_attr_int   (const std::string &name) const;
  void        set_attr_int   (const std::string &name,
                              int value);
  std::string get_attr_string(const std::string &name) const;
  void        set_attr_string(const std::string &name,
                              const std::string &value);

  std::string get_attr_line  (const std::string &name) const;
  mode_set    get_attr_set   (const std::string &name,
                              std::string *pCur = nullptr) const;

  std::string get_attr_from_set(const std::string &name) const;

protected:
  std::string _path;
  mutable int _device_index = -1;
};

//-----------------------------------------------------------------------------

//~autogen generic-class-description classes.motor>currentClass

// The motor class provides a uniform interface for using motors with
// positional and directional feedback such as the EV3 and NXT motors.
// This feedback allows for precise control of the motors. This is the
// most common type of motor, so we just call it `motor`.
//
// The way to configure a motor is to set the '_sp' attributes when
// calling a command or before. Only in 'run_direct' mode attribute
// changes are processed immediately, in the other modes they only
// take place when a new command is issued.

//~autogen
class motor : protected device
{
public:
  typedef device_type motor_type;

  motor(address_type);
  motor(address_type, const motor_type&);

  static constexpr char motor_large[]  = "lego-ev3-l-motor";
  static constexpr char motor_medium[] = "lego-ev3-m-motor";

  using device::connected;
  using device::device_index;

//~autogen generic-declare-property-value classes.motor>currentClass

  // Run the motor until another command is sent.
  static constexpr char command_run_forever[] = "run-forever";

  // Run to an absolute position specified by `position_sp` and then
  // stop using the action specified in `stop_action`.
  static constexpr char command_run_to_abs_pos[] = "run-to-abs-pos";

  // Run to a position relative to the current `position` value.
  // The new position will be current `position` + `position_sp`.
  // When the new position is reached, the motor will stop using
  // the action specified by `stop_action`.
  static constexpr char command_run_to_rel_pos[] = "run-to-rel-pos";

  // Run the motor for the amount of time specified in `time_sp`
  // and then stop the motor using the action specified by `stop_action`.
  static constexpr char command_run_timed[] = "run-timed";

  // Run the motor at the duty cycle specified by `duty_cycle_sp`.
  // Unlike other run commands, changing `duty_cycle_sp` while running *will*
  // take effect immediately.
  static constexpr char command_run_direct[] = "run-direct";

  // Stop any of the run commands before they are complete using the
  // action specified by `stop_action`.
  static constexpr char command_stop[] = "stop";

  // Reset all of the motor parameter attributes to their default value.
  // This will also have the effect of stopping the motor.
  static constexpr char command_reset[] = "reset";

  // Sets the normal polarity of the rotary encoder.
  static constexpr char encoder_polarity_normal[] = "normal";

  // Sets the inversed polarity of the rotary encoder.
  static constexpr char encoder_polarity_inversed[] = "inversed";

  // With `normal` polarity, a positive duty cycle will
  // cause the motor to rotate clockwise.
  static constexpr char polarity_normal[] = "normal";

  // With `inversed` polarity, a positive duty cycle will
  // cause the motor to rotate counter-clockwise.
  static constexpr char polarity_inversed[] = "inversed";

  // Power is being sent to the motor.
  static constexpr char state_running[] = "running";

  // The motor is ramping up or down and has not yet reached a constant output level.
  static constexpr char state_ramping[] = "ramping";

  // The motor is not turning, but rather attempting to hold a fixed position.
  static constexpr char state_holding[] = "holding";

  // The motor is turning, but cannot reach its `speed_sp`.
  static constexpr char state_overloaded[] = "overloaded";

  // The motor is not turning when it should be.
  static constexpr char state_stalled[] = "stalled";

  // Power will be removed from the motor and it will freely coast to a stop.
  static constexpr char stop_action_coast[] = "coast";

  // Power will be removed from the motor and a passive electrical load will
  // be placed on the motor. This is usually done by shorting the motor terminals
  // together. This load will absorb the energy from the rotation of the motors and
  // cause the motor to stop more quickly than coasting.
  static constexpr char stop_action_brake[] = "brake";

  // Does not remove power from the motor. Instead it actively try to hold the motor
  // at the current position. If an external force tries to turn the motor, the motor
  // will `push back` to maintain its position.
  static constexpr char stop_action_hold[] = "hold";



    void run_forever() { set_command("run-forever"); }


  motor() {}

  bool connect(const std::map<std::string, std::set<std::string>>&) noexcept;
};


} // namespace ev3dev

// vim: sw=2
