/*****************************************************************************
 * C Mini-tutorial
 * ---------------
 *
 * Sam McSweeney, 2018
 *
 * This is a mini tutorial aimed primarily at scientists who are familiar with
 * a programming language already (usually Python), and who want to understand
 * the C language and syntax a bit better.
 *
 * This program demostrates the basic use of structs. It implements a struct
 * for representing 3D points
 *
 *****************************************************************************/

#include <stdio.h>

/* The syntax for defining structs is:

     struct [type_name] { [list of variable declarations...] };

*/
struct point3d
{
    double x;
    double y;
    double z;
};

// A function prototype that will be explained below
void cross( struct point3d *, struct point3d *, struct point3d * );


int main()
/* This program sets up two points, calculates their cross product, and prints
 * out the result.
 */
{
    // Let's declare a new point3d, P
    struct point3d P;
    /* At this point, 3 doubles' worth of memory has been allocated. You can
       now use the dot (.) to access the members of point3d just like ordinary
       variables:
    */

    P.x = 1.0;
    P.y = 2.0;
    P.z = 3.0;

    // Let's make another point3d, Q
    struct point3d Q;
    Q.x = -1.0;
    Q.y = -1.5;
    Q.z =  0.5;

    // And finally, let's make a third point3d, R, which will be the result of
    // applying the cross product to P and Q.
    struct point3d R;

    cross( &P, &Q, &R ); //  P x Q --> R

    // Let's print out R, just to make sure it's correct
    printf( "R = { %f, %f, %f }\n", R.x, R.y, R.z );

    // Return success!
    return 0;
}


/* Here is the function that will compute the cross product. Since structs
   can be made up of an arbitrary number of other variables (or other structs,
   for that matter), it is usually preferable to pass pointers to structs,
   rather than the structs themselves, so that you're not copying large
   amounts of data on stack memory. So now, the "output" of our function is
   not the return type, but rather the third struct, which we can access via
   its pointer.
*/

void cross( struct point3d *A, struct point3d *B, struct point3d *C )
/* This function computes the cross product of point3ds A and B,
 * and records the output in C.
 */
{
    /* With structs, there is a different syntax for accessing the member
       variables, depending on whether you are working from the stack variable
       or from a pointer to it. If you have a pointer, then instead of the dot
       (.), use the arrow (->).

       To be crystal clear, in the following, P is a struct, and pP is a
       pointer to it:

         struct point3d P;
         struct point3d *pP = &P;

       Then the following are equivalent:

         P.x   <==>   pP->x
         P.y   <==>   pP->y
         P.z   <==>   pP->z
    */

    C->x = (A->y * B->z) - (A->z * B->y);
    C->y = (A->z * B->x) - (A->x * B->z);
    C->z = (A->x * B->y) - (A->y * B->x);

}

