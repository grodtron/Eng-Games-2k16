#define STOPPER -500                                      /* Smaller than any datum */

template <int MEDIAN_FILTER_SIZE>
class MedianFilter {
    
    private:
      struct pair
      {
          struct pair   *point;               /* Pointers forming list linked in sorted order */
          int16_t  value;                     /* Values to sort */
      };
      
      struct pair buffer[MEDIAN_FILTER_SIZE]; /* Buffer of nwidth pairs */
      struct pair *datpoint;                  /* Pointer into circular buffer of data */
      struct pair small;                      /* Chain stopper */
      struct pair big;                        /* Pointer to head (largest) of linked list.*/
    public:
      MedianFilter(){
        memset ( buffer, 0, MEDIAN_FILTER_SIZE * sizeof(struct pair) );
        datpoint = buffer;
        small = {NULL, STOPPER};
        big = {&small, 0};
      }
    
    public:
      int16_t update(int16_t datum)
      {
          
          struct pair *successor;                              /* Pointer to successor of replaced data item */
          struct pair *scan;                                   /* Pointer used to scan down the sorted list */
          struct pair *scanold;                                /* Previous value of scan */
          struct pair *median;                                 /* Pointer to median */
          int16_t i;
          
          if (datum == STOPPER)
          {
              datum = STOPPER + 1;                             /* No stoppers allowed. */
          }
          
          if ( (++datpoint - buffer) >= MEDIAN_FILTER_SIZE)
          {
              datpoint = buffer;                               /* Increment and wrap data in pointer.*/
          }
          
          datpoint->value = datum;                           /* Copy in new datum */
          successor = datpoint->point;                       /* Save pointer to old value's successor */
          median = &big;                                     /* Median initially to first in chain */
          scanold = NULL;                                    /* Scanold initially null. */
          scan = &big;                                       /* Points to pointer to first (largest) datum in chain */
          
          /* Handle chain-out of first item in chain as special case */
          if (scan->point == datpoint)
          {
              scan->point = successor;
          }
          scanold = scan;                                     /* Save this pointer and   */
          scan = scan->point ;                                /* step down chain */
          
          /* Loop through the chain, normal loop exit via break. */
          for (i = 0 ; i < MEDIAN_FILTER_SIZE; ++i)
          {
              /* Handle odd-numbered item in chain  */
              if (scan->point == datpoint)
              {
                  scan->point = successor;                      /* Chain out the old datum.*/
              }
              
              if (scan->value < datum)                        /* If datum is larger than scanned value,*/
              {
                  datpoint->point = scanold->point;             /* Chain it in here.  */
                  scanold->point = datpoint;                    /* Mark it chained in. */
                  datum = STOPPER;
              };
              
              /* Step median pointer down chain after doing odd-numbered element */
              median = median->point;                       /* Step median pointer.  */
              if (scan == &small)
              {
                  break;                                      /* Break at end of chain  */
              }
              scanold = scan;                               /* Save this pointer and   */
              scan = scan->point;                           /* step down chain */
              
              /* Handle even-numbered item in chain.  */
              if (scan->point == datpoint)
              {
                  scan->point = successor;
              }
              
              if (scan->value < datum)
              {
                  datpoint->point = scanold->point;
                  scanold->point = datpoint;
                  datum = STOPPER;
              }
              
              if (scan == &small)
              {
                  break;
              }
              
              scanold = scan;
              scan = scan->point;
          }
          return median->value;
      }
      
};
