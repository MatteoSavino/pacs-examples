#include <iostream>
#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/interpreter.h>

int
main (void)
{
  // Create interpreter.

  octave::interpreter interpreter;

  try
    {
      
      // Tell the interpreter that we're ready to execute commands:
      int status = interpreter.execute ();

      if (status != 0)
        {
          std::cerr << "creating embedded Octave interpreter failed!"
                    << std::endl;
          return status;
        }

      octave_idx_type n = 2;
      octave_value_list in;

      for (octave_idx_type i = 0; i < n; i++)
        in(i) = octave_value (5 * (i + 2));

      octave_value_list out = octave::feval ("gcd", in, 1);

      if (out.length () > 0)
        std::cout << "GCD of ["
                  << in(0).int_value ()
                  << ", "
                  << in(1).int_value ()
                  << "] is " << out(0).int_value ()
                  << std::endl;
      else
        std::cout << "invalid\n";
    }
  catch (const octave::exit_exception& ex)
    {
      std::cerr << "Octave interpreter exited with status = "
                << ex.exit_status () << std::endl;
    }
  catch (const octave::execution_exception&)
    {
      std::cerr << "error encountered in Octave evaluator!" << std::endl;
    }

  return 0;
}
