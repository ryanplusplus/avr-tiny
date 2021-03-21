/*!
 * @file
 * @brief
 */

void operator delete(void* p)
{
  (void)p;
}

void operator delete(void* p, unsigned s)
{
  (void)p;
  (void)s;
}
