/**************************************************************************
 *
 * Copyright (c) 2012 MediaTek Inc. All Rights Reserved.
 * --------------------
 * This software is protected by copyright and the information contained
 * herein is confidential. The software may not be copied and the information
 * contained herein may not be used or disclosed except with the written
 * permission of MediaTek Inc.
 *
 ***************************************************************************/
/** \file
 * Message digest (hash).
 */
#ifndef A3M_DIGESTMAKER_H
#define A3M_DIGESTMAKER_H

#include <a3m/base_types.h>         /* Base types used by all A3M modules  */
#include <a3m/noncopyable.h>        /* Make class DigestMaker uncopyable   */
#include <a3m/md5.h>                /* Using MD5 algorithm                 */

namespace a3m
{
  class Stream; /* To read/write Digest */

  namespace detail
  {
    /** \defgroup a3mDigestMaker DigestMaker
     * \ingroup  a3mInt
     *
     * A class to create a message digest from a given arbitary number of bytes
     * (usually a file). The nested class is used to store the digest and
     * compare against another digest.
     * @{
     */

    /** DigestMaker class
     * The append() method may be called multiple times to create a digest of
     * several chunks of data. Once the digest() method has been called, do not
     * use the append() method again.
     */
    class DigestMaker : public NonCopyable
    {
    public:
      /** Default constructor */
      DigestMaker();

      /** Append data.
       * May be called multiple times to add more data. Do not call after
       * asking for the digest.
       */
      void append( A3M_CHAR8 const *data,  /**< new data */
                   A3M_UINT32 length /**< number of bytes */ );

      /** Size of the message digest */
      static const A3M_UINT32 DIGEST_SIZE = 16;

      /** Digest class
       * Generated by DigestMaker object. May be compared and read/written
       * to a stream.
       */
      class Digest
      {
      public:
        /** Read from stream.
         */
        void read( Stream &stream /**< input stream */ );
        /** Write to stream.
         */
        void write( Stream &stream /**< output stream */ ) const;

       /** Compare with another Digest.
        * \return A3M_TRUE if identical
        */
        A3M_BOOL operator==( Digest const &other /**< another digest */ ) const;

        friend class DigestMaker;
      private:
        md5_byte_t m_data[DIGEST_SIZE]; // Data for digest
      };

      /** Access Digest.
       * Once this method has been called, do not add more data ussing append()
       * \return reference to the message digest
       */
      Digest const &digest();

    private:
      md5_state_s m_state;   // State used by MD5 functions
      Digest m_digest;       // Calculated when client calls digest() method
      A3M_BOOL m_finished;   // true after client calls digest()
    };

    /** @} */

  } /* namespace detail */
} /* namespace a3m */

#endif /* A3M_DIGESTMAKER_H */
